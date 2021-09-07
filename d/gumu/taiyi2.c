// taiyi2.c
#include <ansi.h>;
inherit ROOM;

void create()
{
	set("short", "̫�ҳ�");
	set("long", @LONG
�����ں�ˮ�ֻ���ú�ˮ����͸�ǡ��������ܸ߷廷�У�����
�̲�������ɽ��ˮӰ���羰���ˡ�����ԭ����̫�ҳصĶ�����̫�۵�
�����������(climb) �ϰ���ԶԶ��ȥ�����ߵ�ɽ��֮���ƺ���һ��
�󶴡��벻����(swim)��ȥ����
LONG
	);
	set("item_desc", ([
		"�����ߡ�" : "�����붫����Զ����ʱ��������ȥ��\n"
		ZJOBACTS2"���ϰ�:climb up\n",
		"��Զɽ��" : "Զ��ɽ��֮���ƺ��и��󶴣���û�����ι�ȥ����ȴ��֪Ϊʲô������ʱ���ڴ�������ȥ��Ī��������ʲô����\n"
		ZJOBACTS2"�ι�ȥ:swim\n",
	]) );
	set("outdoors", "gumu");
	setup();
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_swim", "swim");
}

int do_climb(string arg)
{
	object me = this_player(); 
	int c_exp;
	c_exp = me->query("combat_exp");
	if( !arg || arg != "up")
	{
		write("�Ǹ�����û������\n");
		return 1;
	}

	message_vision("$N��̫�ҳ���������������ȥ��\n", me);
	me->move("/d/gumu/taiyi1");
	message_vision("$N��̫�ҳ���������ȥ��\n", me);
	return 1;
}

int do_swim()
{
	int c_skill;
	object me = this_player();

	c_skill = me->query_skill("jinyan-gong", 1);

	if (me->query("qi") < 40)
		return notify_fail("������������֧��û��������Ӿ��\n");

	me->receive_damage("qi", 20 + random(20));
	message_vision("$N��̫�ҳ��л��˻�ˮ����������������\n", me);
	if (c_skill < 1)
		return 1;

	if (me->can_improve_skill("jinyan-gong") && c_skill < 51)
		me->improve_skill("jinyan-gong",1 + me->query_skill("jinyan-gong", 1) / 15);
	return 1;
}
