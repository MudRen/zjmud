// taiyi1.c
// Java Oct.10 1998
#include <ansi.h>;
inherit ROOM;

void create()
{
	set("short", "̫�ҳ�");
	set("long", @LONG
����ǰ����һ��ɽ������������������̫�ҳ� (chi)����Ϊ��
�챦��������ɣ����ܸ߷廷�У�����̲�������ɽ��ˮӰ���羰
ʮ��������
LONG
	);
	set("outdoors", "gumu");
	set("item_desc", ([
		"��ˮ�С�" : HIG"\n����һ���ܴ��ɽ������̲���������ˮ�峺���ף������̲�ס����(jump)��ȥ����һ����\n"NOR"\n"
		ZJOBACTS2"����ȥ:jump chi\n",
	]));
	set("exits", ([
		"southup"   : __DIR__"shandao3",
	]));

	setup();
}
void init()
{
	add_action("do_jump","jump");
}
int do_jump(string arg)
{
	object me = this_player(); 
	int c_exp;
	c_exp = me->query("combat_exp");
	if( !arg || arg != "chi")
	{
		write("����������ѽ? \n");
		return 1;
	}

	message_vision("$N��̫�ҳ�����ȥ��\n", me);
	me->move("/d/gumu/taiyi2");
	message_vision("$N������̫�ҳ�������\n", me);
	return 1;
}
