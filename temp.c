if(l->start == NULL){
        l->start = n;
        n->next = NULL;
        return;
    }
    if(l->start->size > size){
        n->next = l->start;
        l->start = n;
        return;
    }
    Node *temp = l->start;
    while(temp != NULL){
        //* We are on last node
        if(temp->next == NULL){
            temp->next = n;
            n->next = NULL;
            return;
        }else if(temp->next->size > size){
            n->next = temp->next;
            temp->next = n;
            return;
        }else{
            temp = temp->next;
        }
        
    }