//houhuayuan.c ��԰

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"��԰"NOR);
        set("long", @LONG
��������ݵĺ�԰����෽�и����������ˮ���壬����һ˫�׶죬��
ˮ��������Ϸ�������м���̫��ʯ��ʯ�߷���һ��С����С���Ϸ���һ����¯��
��¯�������������㣬����������ڴ�ͣ����
LONG
        );       
 
	set("outdoors","���");
	set("no_fight",1);
        set("exits", ([
               "south" : __DIR__"xiaojing1",
               "northeast" : __DIR__"citang",
        ]));
        
        set("objects", ([
        ]));
        setup();
}
