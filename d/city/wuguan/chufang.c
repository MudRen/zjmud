//chufang.c
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short","����");
       set("long", @LONG
������ݵĳ���, ��Ȼ����, ���ǹ���ư��, ���ν���, ������ȫ����̨
�϶��������ʹϹ��߲�, �����Ϻ, ���ݵĹ�������㣬ʹ��һ�߽������
��������������������뱥��һ�١��м�����������æµ�š�
LONG);

        set("exits", ([         
                "east" : __DIR__"zoulang1",
        ]));             

        set("objects",([
        ]));

        set("no_fight", 1);

        setup();
}
