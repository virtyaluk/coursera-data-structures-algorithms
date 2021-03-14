# python3

from collections import deque


class SuffixTree(object):
    class Node(object):
        def __init__(self, lab):
            self.lab = lab
            self.out = {}

    def __init__(self, s):
        self.root = self.Node(None)
        self.root.out[s[0]] = self.Node(s)

        for i in range(1, len(s)):
            cur = self.root
            j = i

            while j < len(s):
                if s[j] in cur.out:
                    child = cur.out[s[j]]
                    lab = child.lab
                    k = j + 1

                    while k - j < len(lab) and s[k] == lab[k - j]:
                        k += 1
                    if k - j == len(lab):
                        cur = child
                        j = k
                    else:
                        cExist, cNew = lab[k - j], s[k]
                        mid = self.Node(lab[:k - j])
                        mid.out[cNew] = self.Node(s[k:])
                        child.lab = lab[k - j:]
                        mid.out[cExist] = child
                        cur.out[s[j]] = mid
                else:
                    cur.out[s[j]] = self.Node(s[j:])

    def print(self):
        queue = deque()
        queue.append(self.root)
        while queue:
            u = queue.popleft()
            if u != self.root:
                print(u.lab)
            for label, node in u.out.items():
                queue.append(node)


if __name__ == '__main__':
    text = input()
    stree = SuffixTree(text)
    stree.print()
