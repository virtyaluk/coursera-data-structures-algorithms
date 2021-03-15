# python3

import sys
import threading

sys.setrecursionlimit(10 ** 7)
threading.stack_size(2 ** 27)


class SuffixTree:
    class Node:
        def __init__(self, node, depth, start, end):
            self.parent = node
            self.children = {}
            self.depth = depth
            self.start = start
            self.end = end
            self.visited = False

    def __init__(self, s, order, LCP):
        self.s = s
        self.ele = ['$', 'A', 'C', 'G', 'T']
        self.order = order
        self.LCP = LCP
        self.root = self.Node(None, 0, -1, -1)

    def create_new_leaf(self, node, suffix):
        leaf = self.Node(node, len(self.s) - suffix, suffix + node.depth, len(self.s))

        node.children[self.s[leaf.start]] = leaf

        return leaf

    def break_edge(self, node, mid_start, offset):
        mid_char = self.s[mid_start]
        left_char = self.s[mid_start + offset]
        mid = self.Node(node, node.depth + offset, mid_start, mid_start + offset)

        mid.children[left_char] = node.children[mid_char]
        node.children[mid_char].parent = mid
        node.children[mid_char].start += offset
        node.children[mid_char] = mid

        return mid

    def st_from_sa(self):
        lcp_prev = 0
        cur = self.root

        for i in range(len(self.s)):
            suffix = self.order[i]

            while cur.depth > lcp_prev:
                cur = cur.parent

            if cur.depth == lcp_prev:
                cur = self.create_new_leaf(cur, suffix)
            else:
                mid_start = self.order[i - 1] + cur.depth
                offset = lcp_prev - cur.depth
                mid = self.break_edge(cur, mid_start, offset)
                cur = self.create_new_leaf(mid, suffix)

            if i < len(self.s) - 1:
                lcp_prev = self.LCP[i]

    def print_edges(self, cur):
        cur.visited = True

        if cur != self.root:
            print(cur.start, cur.end)

        for i in range(5):
            child = cur.children.get(self.ele[i], None)

            if child is not None and not child.visited:
                self.print_edges(child)


def main():
    text = input()
    suffix_array = list(map(int, input().split()))
    lcp = list(map(int, input().split()))

    print(text)

    suffix_tree = SuffixTree(text, suffix_array, lcp)
    suffix_tree.st_from_sa()
    suffix_tree.print_edges(suffix_tree.root)


threading.Thread(target=main).start()
