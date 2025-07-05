use std::io::{self, BufRead};

#[derive(Debug)]
struct Node<T> {
    value: T,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

struct BinaryTree<T> {
    root: Option<Box<Node<T>>>
}

impl<T: Ord> BinaryTree<T> {
    fn new() -> Self {
        Self {root : None}
    }

    fn insert(&mut self, value: T) {
        self.root = Self::insert_node(self.root.take(), value);
    }

    fn insert_node(node: Option<Box<Node<T>>>, value: T) -> Option<Box<Node<T>>> {
        match node {
            Some (mut boxed_node) => {
                if value < boxed_node.value {
                    boxed_node.left = Self::insert_node(boxed_node.left.take(), value);
                } else {
                    boxed_node.right = Self::insert_node(boxed_node.right.take(), value);
                }
                Some(boxed_node)
            }
            None => {
                Some(Box::new(Node {
                    value,
                    left: None,
                    right: None
                }))
            }
        }
    }
}

fn read_lines() -> Vec<i32> {
    let mut vec = Vec::new();
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        match line {
            Ok(l) => {
                let n = l.trim().parse::<i32>().unwrap();
                vec.push(n);
            },
            Err(_) => break,
        };
    }
    vec
}

fn create_tree(numbers: Vec<i32>) -> BinaryTree<i32> {
    let mut tree = BinaryTree::<i32>::new();

    for n in numbers {
        if tree.root.is_none() {
            tree.insert(n);
            continue;
        }
        let mut current = tree.root.as_mut();

        while let Some(node) = current {
            if n < node.value {
                if node.left.is_none() {
                    node.left = Some(Box::new(Node {
                        value: n,
                        left: None,
                        right: None,
                    }));
                    break;
                } else {
                    current = node.left.as_mut();
                }
            } else {
                if node.right.is_none() {
                    node.right = Some(Box::new(Node {
                        value: n,
                        left: None,
                        right: None,
                    }));
                    break;
                } else {
                    current = node.right.as_mut();
                }
            }
        }
    }

    tree
}

fn post_traversal(node: Option<&Box<Node<i32>>>) {
    if let Some(current_node) = node {
        post_traversal(current_node.left.as_ref());
        post_traversal(current_node.right.as_ref());
        println!("{}", current_node.value);
    }
}

fn main() {
    let numbers = read_lines();
    
    let tree = create_tree(numbers);

    post_traversal(tree.root.as_ref());
}