# stack = []

# def peek():
#     print(stack[-1])


# stack.append(3)
# stack.append(4)
# peek()
# print(stack)
# print(stack.pop())
# print(stack)



#  stack using linkedlist
class Node:
    def __init__(self,data=None,next =None) :
        self.data=data
        self.next=next
        
class LinkedList:
    def __init__(self):
        self.head =None
        
    def push(self,data):
        node = Node(data,self.head)
        self.head =node
        
    def pop(self):
        if self.head == 0:
            raise Exception("UnderFlow")
        self.head = self.head.next
        
    def peek(self):
        print(self.head.data)
        
    def show(self):
        itr = self.head
        stack = ''
        while itr:
            stack += str(itr.data) + '-->'

            itr = itr.next
        print(stack)

if __name__=='__main__':
    stack = LinkedList()
    stack.push(10)
    stack.push(20)
    stack.show()
    stack.pop()
    stack.show()
    stack.push(30)
    stack.show()