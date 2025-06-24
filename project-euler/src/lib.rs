use std::{
    cell::RefCell,
    fs::File,
    io::{self, BufRead, BufReader},
    rc::Rc,
};

type NodeLink = Rc<RefCell<Node>>;

#[derive(Debug, Clone)]
pub struct Node {
    pub val: i32,
    pub left_child: Option<NodeLink>,
    pub right_child: Option<NodeLink>,
}

impl Node {
    pub fn new(val: i32) -> NodeLink {
        Rc::new(RefCell::new(Node {
            val,
            left_child: None,
            right_child: None,
        }))
    }
}

fn build_tree(path: &str) -> io::Result<NodeLink> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);

    let mut prev_row: Vec<NodeLink> = Vec::new();
    let mut root: Option<NodeLink> = None;

    for line in reader.lines() {
        let line = line?;
        let curr_row: Vec<_> = line
            .split_whitespace()
            .map(|s| Node::new(s.parse().expect("bad int: {s}")))
            .collect();
        // this line executes on the very first row
        if root.is_none() {
            root = Some(curr_row[0].clone());
        }

        for j in 0..prev_row.len() {
            let mut parent = prev_row[j].borrow_mut();
            parent.left = Some(curr_row[j].clone());
            parent.right = Some
        }
    }

    todo!()
}
