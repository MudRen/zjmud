//Room: majiu.c ���
#include <room.h>
inherit TRANS_ROOM;
void create()
{
      set("short","���");
      set("long",@LONG
����Ȫ�ݳǵ���ǣ����깩Ӧ���ʲ��ϡ�Ȫ����ҵ������������
����¡������Ǻ����տ���ƥ��������ι�����㣬��ϴˢ�ø�Ǭ������һ
ֱ�ź򵽿�����·����������µ���ľ���϶���һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "quanzhou");
      set("no_fight", 1);
      set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,
 
      ]));
      set("exits",([ /* sizeof() == 1 */
		"northwest" : __DIR__"zhongxin",
      ]));
      setup();
      replace_program(TRANS_ROOM);
}
