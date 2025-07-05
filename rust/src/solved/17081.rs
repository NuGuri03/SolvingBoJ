use std::{
    cmp::{max, min},
    io::{self, Stdout, Write},
};

static mut SPIKE_DAMAGE: i32 = 5;

#[derive(PartialEq, Clone, Copy)]
enum Accessory {
    HR,
    RE,
    CO,
    EX,
    DX,
    HU,
    CU,
}
impl Accessory {
    pub fn hp_regeneration(player: &mut Player) {
        player.hp = min(player.hp + 3, player.get_max_health());
    }

    pub fn reincarnation(player: &mut Player) {
        if player.hp > 0 {
            return;
        }

        player.hp = player.get_max_health();
        player.pos = player.init_pos;

        let idx = player.get_accessory_effect_index(Self::RE);
        if idx == -1 {
            return;
        }
        player.accessories.remove(idx as usize);
    }

    pub fn courage(player: &Player) -> i32 {
        let idx = player.get_accessory_effect_index(Self::DX);

        if idx == -1 {
            (player.att + player.weapon) * 2
        } else {
            (player.att + player.weapon) * 3
        }
    }

    pub fn experience(exp: usize) -> usize {
        (exp as f64 * 1.2) as usize
    }

    pub fn dexterity() {
        unsafe {
            SPIKE_DAMAGE = 1;
        }
    }

    pub fn hunter(player: &mut Player) {
        player.hp = player.get_max_health();
    }
}

struct Item {
    pos: (usize, usize),
    accessory: Option<Accessory>,
    weapon: Option<i32>,
    armor: Option<i32>,
}
impl Item {
    pub fn new(
        pos: (usize, usize),
        accessory: Option<Accessory>,
        weapon: Option<i32>,
        armor: Option<i32>,
    ) -> Self {
        Self {
            pos,
            accessory,
            weapon,
            armor,
        }
    }
}

#[derive(Clone)]
struct Monster {
    pos: (usize, usize),
    name: String,
    att: i32,
    def: i32,
    hp: i32,
    exp: usize,
}
impl Monster {
    pub fn new(pos: (usize, usize), name: String, att: i32, def: i32, hp: i32, exp: usize) -> Self {
        Self {
            pos,
            name,
            att,
            def,
            hp,
            exp,
        }
    }

    pub fn damaged(&mut self, damage: i32) {
        self.hp -= damage;
    }

    pub fn is_died(&self) -> bool {
        self.hp <= 0
    }
}

struct Player {
    init_pos: (usize, usize),
    pos: (usize, usize),
    curr_tile: char,
    lv: usize,
    exp: usize,
    hp: i32,
    att: i32,
    def: i32,
    weapon: i32,
    armor: i32,
    accessories: Vec<Accessory>,
    win: bool,
}
impl Player {
    pub fn new(pos: (usize, usize)) -> Self {
        Player {
            init_pos: pos,
            pos,
            curr_tile: '.',
            lv: 1,
            exp: 0,
            hp: 20,
            att: 2,
            def: 2,
            weapon: 0,
            armor: 0,
            accessories: Vec::new(),
            win: false,
        }
    }

    /***********************************************/

    fn is_alive(&mut self) -> bool {
        self.hp > 0
    }

    pub fn get_max_health(&self) -> i32 {
        20 + (self.lv as i32 - 1) * 5
    }

    pub fn get_max_exp(&self) -> usize {
        self.lv * 5
    }

    /***********************************************/

    fn damaged(&mut self, damage: i32) {
        self.hp -= damage;
    }

    fn attack_monster(&self, monster: &mut Monster, tries: usize) {
        let mut att = self.att + self.weapon;

        let co_idx = self.get_accessory_effect_index(Accessory::CO);
        if co_idx != -1 && tries == 0 {
            att = Accessory::courage(self);
        }

        monster.damaged(max(1, att - monster.def));
    }

    fn defend_monster(&mut self, monster: &Monster) {
        self.damaged(max(1, monster.att - (self.def + self.armor)));
    }

    /***********************************************/

    fn get_experience(&mut self, monster: &Monster) {
        let mut exp = monster.exp;
        let ex_idx = self.get_accessory_effect_index(Accessory::EX);
        if ex_idx != -1 {
            exp = Accessory::experience(exp);
        }

        self.exp += exp;

        if self.exp >= self.get_max_exp() {
            self.level_up();
        }
    }

    fn level_up(&mut self) {
        self.lv += 1;

        self.exp = 0;
        self.hp = self.get_max_health();
        self.att += 2;
        self.def += 2;
    }

    /***********************************************/

    fn revive(&mut self) -> bool {
        let re_idx = self.get_accessory_effect_index(Accessory::RE);

        if re_idx == -1 {
            false
        } else {
            Accessory::reincarnation(self);
            true
        }
    }

    /***********************************************/

    fn earn_weapon(&mut self, weapon: i32) {
        self.weapon = weapon;
    }

    fn earn_armor(&mut self, armor: i32) {
        self.armor = armor;
    }

    fn earn_accessory(&mut self, accessory: Accessory) {
        if self.accessories.len() >= 4 {
            return;
        }

        for acc in &self.accessories {
            if *acc == accessory {
                return;
            }
        }

        self.accessories.push(accessory);
    }

    pub fn get_accessory_effect_index(&self, accessory: Accessory) -> i32 {
        let mut i = 0;
        for acc in &self.accessories {
            if *acc == accessory {
                return i;
            }
            i += 1;
        }
        -1
    }

    /********************************************************************************/

    fn meet_item_box(&mut self, grid: &mut Grid) {
        let mut item = None;
        for it in &grid.items {
            if it.pos == self.pos {
                item = Some(it);
                break;
            }
        }

        if let Some(item) = item {
            if let Some(accessory) = item.accessory {
                self.earn_accessory(accessory);
            }
            if let Some(weapon) = item.weapon {
                self.earn_weapon(weapon);
            }
            if let Some(armor) = item.armor {
                self.earn_armor(armor);
            }

            // Out-of-bounds check
            if self.pos.0 < grid.maze.len() && self.pos.1 < grid.maze[0].len() {
                grid.maze[self.pos.0][self.pos.1] = '.';
            }
        } else {
            // 예외처리: 아이템이 없는 경우 무시
        }
    }

    fn meet_spike_trap(&mut self) -> bool {
        let idx = self.get_accessory_effect_index(Accessory::DX);

        if idx != -1 && unsafe { SPIKE_DAMAGE == 5 } {
            Accessory::dexterity();
        }

        unsafe {
            self.damaged(SPIKE_DAMAGE);
        }

        self.is_alive()
    }

    fn meet_monster(&mut self, grid: &mut Grid, is_boss: bool) -> bool {
        // 몬스터 찾기 (mutable ref)
        let mut monster_idx = None;
        for (i, mon) in grid.monsters.iter_mut().enumerate() {
            if mon.pos == self.pos {
                monster_idx = Some(i);
                break;
            }
        }

        if let Some(idx) = monster_idx {
            let monster = &mut grid.monsters[idx];
            let original_monster_hp = monster.hp;

            // 몬스터와 전투 시작
            let mut tries = 0;
            while self.is_alive() {
                self.attack_monster(monster, tries);

                if is_boss && tries == 0 {
                    let hu_idx = self.get_accessory_effect_index(Accessory::HU);
                    if hu_idx != -1 {
                        Accessory::hunter(self);
                    }
                }

                if monster.is_died() {
                    break;
                }

                self.defend_monster(monster);

                if is_boss && tries == 0 {
                    let hu_idx = self.get_accessory_effect_index(Accessory::HU);
                    if hu_idx != -1 {
                        Accessory::hunter(self);
                    }
                }

                tries += 1;
            }

            // 전투 종료

            // 사망
            if !self.is_alive() {
                monster.hp = original_monster_hp;
                return false;
            }

            // 생존
            let hr_idx = self.get_accessory_effect_index(Accessory::HR);
            if hr_idx != -1 {
                Accessory::hp_regeneration(self);
            }

            self.get_experience(monster);
            true
        } else {
            // 예외처리: 몬스터가 없으면 false
            false
        }
    }

    /********************************************************************************/

    pub fn move_player(&mut self, grid: &mut Grid, ch: char) {
        let mut next_pos = self.pos;
        match ch {
            'L' => next_pos.1 = next_pos.1.saturating_sub(1),
            'R' => next_pos.1 = next_pos.1.saturating_add(1),
            'U' => next_pos.0 = next_pos.0.saturating_sub(1),
            'D' => next_pos.0 = next_pos.0.saturating_add(1),
            _ => return, // 잘못된 입력 무시
        }

        // index out of bounds 예외처리
        let maze_h = grid.maze.len();
        let maze_w = grid.maze[0].len();
        let in_maze = next_pos.0 < maze_h && next_pos.1 < maze_w;

        let is_blocked = if in_maze {
            grid.maze[next_pos.0][next_pos.1] == '#'
        } else {
            true
        };

        // 이동할 위치 선정
        if !is_blocked && in_maze {
            grid.maze[self.pos.0][self.pos.1] = self.curr_tile;
            self.pos = next_pos;
        }

        let mut next_tile = if in_maze {
            grid.maze[self.pos.0][self.pos.1]
        } else {
            self.curr_tile
        };
        if is_blocked {
            next_tile = self.curr_tile;
        }
        match next_tile {
            '.' => {
                self.curr_tile = '.';
                grid.maze[self.pos.0][self.pos.1] = '@';
            }
            'B' => {
                self.meet_item_box(grid);

                self.curr_tile = grid.maze[self.pos.0][self.pos.1];
                grid.maze[self.pos.0][self.pos.1] = '@';
            }

            '^' => {
                let prev_pos = self.pos;

                if self.meet_spike_trap() {
                    self.curr_tile = '^';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else if self.revive() {
                    if prev_pos.0 < maze_h && prev_pos.1 < maze_w {
                        grid.maze[prev_pos.0][prev_pos.1] = '^';
                    }
                    self.curr_tile = '.';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else {
                    grid.maze[self.pos.0][self.pos.1] = '^';
                }
            }
            '&' => {
                let prev_pos = self.pos;

                if self.meet_monster(grid, false) {
                    self.curr_tile = '.';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else if self.revive() {
                    if prev_pos.0 < maze_h && prev_pos.1 < maze_w {
                        grid.maze[prev_pos.0][prev_pos.1] = '&';
                    }
                    self.curr_tile = '.';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else {
                    grid.maze[self.pos.0][self.pos.1] = '&';
                }
            }
            'M' => {
                let prev_pos = self.pos;

                if self.meet_monster(grid, true) {
                    self.win = true;
                    self.curr_tile = '.';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else if self.revive() {
                    if prev_pos.0 < maze_h && prev_pos.1 < maze_w {
                        grid.maze[prev_pos.0][prev_pos.1] = 'M';
                    }
                    self.curr_tile = '.';
                    grid.maze[self.pos.0][self.pos.1] = '@';
                } else {
                    grid.maze[self.pos.0][self.pos.1] = 'M';
                }
            }
            _ => {
                // 잘못된 문자 무시
            }
        }
    }
}

struct Grid {
    maze: Vec<Vec<char>>,
    monsters: Vec<Monster>,
    items: Vec<Item>,
}

fn read_maze_size() -> (usize, usize) {
    let mut s = String::new();
    if io::stdin().read_line(&mut s).is_err() {
        return (1, 1); // 입력 예외
    }

    let integers: Vec<usize> = s
        .split_ascii_whitespace()
        .take(2)
        .filter_map(|s| s.parse().ok())
        .collect();

    if integers.len() != 2 {
        return (1, 1); // 입력 예외
    }

    (integers[0], integers[1])
}

fn read_maze(
    n: usize,
    m: usize,
    k: &mut usize,
    l: &mut usize,
    player_init_position: &mut (usize, usize),
) -> Vec<Vec<char>> {
    let mut maze = vec![vec!['0'; m + 2]; n + 2];

    for i in 0..n + 2 {
        maze[i][0] = '#';
        maze[i][m + 1] = '#';
    }

    for j in 0..m + 2 {
        maze[0][j] = '#';
        maze[n + 1][j] = '#';
    }

    for i in 1..=n {
        let mut s = String::new();
        if io::stdin().read_line(&mut s).is_err() {
            continue; // 입력 예외처리
        }

        let mut j = 1;
        for ch in s.trim().chars() {
            if j > m {
                break; // oversize in maze 예외처리
            }

            if ch == '&' || ch == 'M' {
                *k += 1;
            }

            if ch == 'B' {
                *l += 1;
            }

            if ch == '@' {
                (*player_init_position) = (i, j);
            }

            maze[i][j] = ch;
            j += 1;
        }
    }

    maze
}

fn read_player_move() -> String {
    let mut s = String::new();
    if io::stdin().read_line(&mut s).is_err() {
        return String::new();
    }

    s.trim().to_string()
}

fn read_monster_information(k: usize) -> Vec<Monster> {
    let mut monster_info = Vec::new();

    for _ in 0..k {
        let mut s = String::new();
        if io::stdin().read_line(&mut s).is_err() {
            continue;
        }

        let tokens: Vec<String> = s.split_ascii_whitespace().map(|s| s.to_string()).collect();

        if tokens.len() < 7 {
            continue; // 예외처리
        }

        let n = tokens[0].parse::<usize>().unwrap_or(1);
        let m = tokens[1].parse::<usize>().unwrap_or(1);

        let pos = (n, m);
        let name = tokens[2].clone();
        let att = tokens[3].parse::<i32>().unwrap_or(1);
        let def = tokens[4].parse::<i32>().unwrap_or(1);
        let hp = tokens[5].parse::<i32>().unwrap_or(1);
        let exp = tokens[6].parse::<usize>().unwrap_or(1);

        let monster = Monster::new(pos, name, att, def, hp, exp);

        monster_info.push(monster);
    }

    monster_info
}

fn read_item_information(l: usize) -> Vec<Item> {
    let mut items = Vec::new();

    for _ in 0..l {
        let mut s = String::new();
        if io::stdin().read_line(&mut s).is_err() {
            continue;
        }

        let tokens: Vec<String> = s.split_ascii_whitespace().map(|s| s.to_string()).collect();

        if tokens.len() < 4 {
            continue; // 예외처리
        }

        let n = tokens[0].parse::<usize>().unwrap_or(1);
        let m = tokens[1].parse::<usize>().unwrap_or(1);

        let pos = (n, m);
        let item_type = tokens[2].chars().next().unwrap_or('O');
        let mut accessory = None;
        let mut weapon = None;
        let mut armor = None;

        match item_type {
            'O' => {
                if tokens.len() < 4 {
                    continue;
                }
                let acc = tokens[3].as_str();
                match acc {
                    "HR" => accessory = Some(Accessory::HR),
                    "RE" => accessory = Some(Accessory::RE),
                    "CO" => accessory = Some(Accessory::CO),
                    "EX" => accessory = Some(Accessory::EX),
                    "DX" => accessory = Some(Accessory::DX),
                    "HU" => accessory = Some(Accessory::HU),
                    "CU" => accessory = Some(Accessory::CU),
                    _ => {}
                }
            }
            'A' => {
                if tokens.len() < 4 {
                    continue;
                }
                armor = tokens[3].parse::<i32>().ok();
            }
            'W' => {
                if tokens.len() < 4 {
                    continue;
                }
                weapon = tokens[3].parse::<i32>().ok();
            }
            _ => {
                continue;
            }
        }
        let item = Item::new(pos, accessory, weapon, armor);

        items.push(item);
    }

    items
}

fn print_state(
    stdout: &mut Stdout,
    n: usize,
    m: usize,
    passed_turns: usize,
    player: &Player,
    grid: &Grid,
) {
    for i in 1..=n {
        for j in 1..=m {
            write!(
                stdout,
                "{}",
                grid.maze.get(i).and_then(|row| row.get(j)).unwrap_or(&'#')
            )
            .unwrap();
        }
        writeln!(stdout).unwrap();
    }

    writeln!(stdout, "Passed Turns : {}", passed_turns).unwrap();

    writeln!(stdout, "LV : {}", player.lv).unwrap();
    writeln!(
        stdout,
        "HP : {}/{}",
        max(0, player.hp),
        player.get_max_health()
    )
    .unwrap();
    writeln!(stdout, "ATT : {}+{}", player.att, player.weapon).unwrap();
    writeln!(stdout, "DEF : {}+{}", player.def, player.armor).unwrap();
    writeln!(stdout, "EXP : {}/{}", player.exp, player.get_max_exp()).unwrap();

    if player.hp > 0 {
        writeln!(
            stdout,
            "{}",
            match player.win {
                true => "YOU WIN!",
                false => "Press any key to continue.",
            }
        )
        .unwrap();
    } else {
        let mut died_cause = None;
        for m in &grid.monsters {
            if m.pos == player.pos {
                died_cause = Some(m.name.clone());
                break;
            }
        }

        if grid
            .maze
            .get(player.pos.0)
            .and_then(|row| row.get(player.pos.1))
            .copied()
            == Some('^')
        {
            died_cause = Some("SPIKE TRAP".to_string());
        }

        writeln!(
            stdout,
            "YOU HAVE BEEN KILLED BY {}..",
            died_cause.unwrap_or("UNKNOWN".to_string())
        )
        .unwrap();
    }
}

fn main() {
    let mut stdout = io::stdout();

    let (n, m) = read_maze_size();
    let mut k = 0;
    let mut l = 0;
    let mut player_init_position = (0, 0);

    let maze = read_maze(n, m, &mut k, &mut l, &mut player_init_position);
    let s = read_player_move();
    let monsters = read_monster_information(k);
    let items = read_item_information(l);

    let mut player = Player::new(player_init_position);
    let mut grid = Grid {
        maze,
        monsters,
        items,
    };

    let mut passed_turns = 0;
    for ch in s.chars() {
        passed_turns += 1;

        player.move_player(&mut grid, ch);

        // println!("\nMOVE {ch}");
        // print_state(&mut stdout, n, m, passed_turns, &player, &grid);

        if player.hp <= 0 || player.win {
            break;
        }
    }

    print_state(&mut stdout, n, m, passed_turns, &player, &grid);
}
