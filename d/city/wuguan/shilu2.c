//shilu2.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
����һ����ʯ���̳ɵ�С·�������������񣬲�ʱ��Щ���˺�Ѿ�ߴ�����
��������ȥ���������������䳡�ˣ����洫����ƥ��˻�����������洫���ܳ�
�ӵ�����������ȴ�Ǿ����ĵġ�
LONG);
        
	set("no_fight", 1); 
	//set("outdoors","���");

        set("exits", ([
               "north" : __DIR__"wuchang2",
               "south" : __DIR__"mafang",
               "east" : __DIR__"shuifang",
	       "west" : __DIR__"mufang",
        ]));          

        setup();
}
