//pianting2.c 

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",YEL"������"NOR);
        set("long", @LONG
���������ǽ�ϵ����˻�ѡ����ＫΪ�����������������Ƴ�������ص�
��������������������ذ��ż������ţ������������衣������������ǵ�ָ
�������������ϴ�����dazuo)�����ɣ�tuna����������һ��ʯ��·��
LONG
        );        
  
        set("exits", ([
               "north" : __DIR__"shilu4",               
        ]));
       set("no_fight",1);
        set("objects", ([
               __DIR__"npc/dizi8" : 1,
        ]));

        setup();
}
