//Room: majiu.c ���

#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","���");
      set("long",@LONG
���ǳɶ��ǵ���ǣ����깩Ӧ���ʲ��ϡ��ɶ���紾�ӣ�����ǻ��
��ǣ����Ǻ����տ���������ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź�
������·����������µ���ľ���϶���һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "city3");
      set("no_fight", 1);
      set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,
	    
      ]));
      set("exits",([ /* sizeof() == 1 */
		"west" : __DIR__"kedian",
      ]));
      setup();
      replace_program(TRANS_ROOM);
}
