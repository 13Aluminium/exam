class Node:
    def __init__(self,data=None,next=None):
        self.data=data
        self.next=next

class LinkedList:
    def __init__(self):
        self.head=None
    def insert_at_beg(self,data):
        # create a node with the help of NOde class where data is data and next is head as we are inserting at the beginninh
        node = Node(data,self.head)
        # now assign the head poiinter the new added node
        self.head = node
    def insert_at_end(self,data):
        if self.head is None:
            self.head = Node(data,None)
            return
        itr= self.head
        while itr.next:
            itr = itr.next
        
        itr.next = Node(data,None)
    
    def insert_values(self,data_list):
        self.head = None
        for data in data_list:
            self.insert_at_end(data)
        
    def print(self):
        if self.head is None:
            print("Linked List is empty")
            return

        # creating a variable for itrerating thru whole linked list
        itr = self.head
        llstr = ''
        while itr:
            llstr += str(itr.data) + '-->'
            itr = itr.next
        print(llstr)
    def get_len(self):
        count = 0
        itr = self.head
        while itr:
            count +=1
            itr =itr.next
        return count
        print(count)
        
        
    def remove_at(self,index):
        if index<0 or index>=self.get_len():
            raise Exception("Invalid Index")
        if index == 0:
            self.head = self.head.next
        
        count = 0
        itr = self.head
        while itr:
            if count == index -1:
                itr.next = itr.next.next
                
                break
            itr = itr.next
            count +=1
            
    def insert_at(self,index,data):
        if index<0 or index >self.get_len():
            raise Exception("INvalid Index")
        if index == 0:
            self.insert_at_beg(data)
        if index == self.get_len():
            self.insert_at_end(data)
        
        count = 0
        itr =self.head
        while itr  :
            if count == index-1:
                 itr.next=Node(data,itr.next)
                 break

            itr =itr.next
            count +=1
            
            
    def insert_at_value(self,value,data):
        count = 0
        itr = self.head
        while itr:
            if itr.data == value:
                itr.next = Node(data,itr.next)
                break
            itr = itr.next
            count +=1
    
    def remove_at_value(self,value):
        count = 0
        itr = self.head
        while itr:
            if itr.data==value:
                itr.next =itr.next.next
                break
            itr =itr.next
            count+=1
            
if __name__=='__main__':
    ll = LinkedList()
    ll.insert_values([1,2,3,4,5,6,7,8])
    

    ll.print()
    # ll.remove_at(2)
    ll.insert_at_value(5,100)
    ll.remove_at_value(3)

    # ll.insert_at(5,100)

    ll.print()
    ll.get_len()