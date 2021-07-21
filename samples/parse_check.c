#include "md.h"
#include "md.c"

static MD_Arena *arena = 0;

int main(int argument_count, char **arguments)
{
    MD_ThreadContext tctx;
    MD_ThreadInit(&tctx);
    
    arena = MD_ArenaNew(1ull << 40);
    
    MD_Node *list = MD_MakeList(arena);
    for(int i = 1; i < argument_count; i += 1)
    {
        MD_Node *root = MD_ParseWholeFile(arena, MD_S8CString(arguments[i])).node;
        MD_PushNewReference(arena, list, root);
    }
    
    for(MD_EachNodeRef(root, list->first_child))
    {
        for(MD_EachNode(node, root->first_child))
        {
            MD_DebugOutputTree(stdout, node, 0);
        }
    }
    
    return 0;
}
