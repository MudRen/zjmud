//xiaojing1.c by river

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
һ�����������ö���ʯ�̳ɵ�С��, ·������������, һ����ɽʯ��ľ��
׺�����С�������ʯ���ϣ�����ž�žવط�������������ǰ���е�С�ţ�
�����ž��ܵ���԰�ˡ�
LONG
        );        
	
	//set("outdoors","���");
	set("no_fight",1);
        set("exits", ([
               "north" : __DIR__"houhuayuan",
               "south" : __DIR__"xiaojing2",
        ]));
        
        set("objects", ([
        ]));

        setup();
}
