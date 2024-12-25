function ListNode(val, next) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
}
/**
* @param {ListNode[]} lists
* @return {ListNode}
*/
var mergeKLists = function(lists) {
   current = ListNode();
   return merge(lists, current).next;
};

function merge(lists, current) {
   let take = 0;
   for (i = 0; i < lists.length; i++) {
       if (lists[i].val < lists[take].val) {
        take = i;
       }
   }
   lists[take] = lists[take].next;
   current.next = merge(lists)
   return current;
}