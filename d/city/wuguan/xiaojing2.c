//xiaojing2.c by river

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
һ�����������ö���ʯ�̳ɵ�С��, ·������������, һ����ɽʯ��ľ��
׺�����С�������ʯ���ϣ�����ž�žવط����������������������Ż��ȣ�
������ȥ������С�������죬���������ϼͤ�ˡ�
LONG
        );
        
        //set("outdoors","���");
	  set("no_fight",1);
        set("exits", ([
               "north" : __DIR__"xiaojing1",
	       "east"  : __DIR__"wxting",
	       "west"  : __DIR__"huilang",
        ]));
        
        set("objects", ([
        ]));

        setup();
}
