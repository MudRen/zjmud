//Room: majiu.c ���
#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","���");
      set("long",@LONG
���ǳ����ǵ���ǣ����깩Ӧ���ʲ��ϡ��������ڸ�ԣ�������̼���
�࣬�������Ƕ�������տ���������ι�����㣬��ϴˢ�ø�Ǭ������һ
ֱ�ź򵽿�����·����������µ���ľ���϶���һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "changan");
      set("no_fight", 1);
      set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,
	       
      ]));
      set("exits",([ /* sizeof() == 1 */
		"south" : __DIR__"huarui1",
      ]));
      setup();
      replace_program(TRANS_ROOM);
}
