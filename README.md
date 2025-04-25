# 🚀 DAA Hackathon

Welcome to the **DAA Hackathon** project!  
This repository showcases a solution to the *Optimal Binary Search Tree with Rotation Costs* problem — a twist on the classic Dynamic Programming challenge, where we minimize search cost while also factoring in rotation penalties.

---

## 📌 Problem Statement

Construct a Binary Search Tree (BST) from sorted keys with known access frequencies such that:

- The **total search cost** is minimized.
- Each **rotation operation** (used during balancing) incurs a fixed penalty.
- Final cost = **Search cost** + **Rotation cost**

---

## 🧠 Approach

We use **Dynamic Programming** to explore all possible BST configurations. For each subarray of keys, we:
- Try all possible roots.
- Compute the cost of left and right subtrees.
- Add rotation penalties for left/right subtrees.
- Track and memoize the minimum cost.

---

## 💡 Sample Input

