//Room: majiu.c ���
#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","���");
      set("long",@LONG
���ǹ������ǣ�����ຮ֮�أ��ķ����ʲ��ϡ��������󺺹��ܳ�
�࣬����ǻ����ǣ����Ǻ����տ���������ι�����㣬��ϴˢ�ø�Ǭ��
����һֱ�ź򵽿�����·�����ѩ���µ�ľ���϶���һ����ľ�ơ�
LONG);
      set("outdoors", "guanwai");
      set("no_fight", 1);
      set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

      ]));
      set("exits",([ /* sizeof() == 1 */
	  "east"      : __DIR__"kedian",
      ]));
      setup();
      replace_program(TRANS_ROOM);
}
