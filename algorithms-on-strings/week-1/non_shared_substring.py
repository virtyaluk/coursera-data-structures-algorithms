# python3

import sys
import threading

sys.setrecursionlimit(10 ** 7)
threading.stack_size(2 ** 25)


class SuffixTree:
    class Node:
        def __init__(self, label):
            self.label = label
            self.out = {}
            self.type = 'L'
            self.visited = False
            self.parent = None

    def __init__(self, s):
        self.root = self.Node(None)
        self.root.out[s[0]] = self.Node(s)

        for i in range(1, len(s)):
            j = i
            cur = self.root
            while j < len(s):
                if s[j] in cur.out:
                    child = cur.out[s[j]]
                    label = child.label
                    k = j + 1

                    while k - j < len(label) and s[k] == label[k - j]:
                        k += 1

                    if k - j == len(label):
                        j = k
                        cur = child
                    else:
                        cExist, cNew = label[k - j], s[k]
                        mid = self.Node(label[:k - j])
                        mid.out[cNew] = self.Node(s[k:])
                        child.label = label[k - j:]
                        mid.out[cExist] = child
                        cur.out[s[j]] = mid
                else:
                    cur.out[s[j]] = self.Node(s[j:])

    def explore(self, cur, Lleaves):
        cur.visited = True

        if len(cur.out) == 0:
            if '#' not in cur.label:
                cur.type = 'R'
            else:
                Lleaves.append(cur)
        else:
            for a, node in cur.out.items():
                if not node.visited:
                    node.parent = cur
                    self.explore(node, Lleaves)
            for a, node in cur.out.items():
                if node.type == 'R':
                    cur.type = 'R'

    def shortest_uncommon_string(self):
        Lleaves = []

        self.explore(self.root, Lleaves)

        results = []

        for leaf in Lleaves:
            char = ''
            substring = ''
            cur = leaf.parent

            if leaf.label[0] == '#' and cur.type == 'R':
                continue
            elif cur.type == 'R':
                char += leaf.label[0]

            while cur != self.root:
                substring = cur.label + substring
                cur = cur.parent

            substring += char
            results.append(substring)
        result = min(results, key=lambda x: len(x))

        return result


def main():
    s = input()
    t = input()

    text = s + '#' + t + '$'
    suffix_tree = SuffixTree(text)
    result = suffix_tree.shortest_uncommon_string()

    print(result)


threading.Thread(target=main).start()
