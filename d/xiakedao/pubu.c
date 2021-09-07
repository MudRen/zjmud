// pubu.c �ٲ�

inherit ROOM;

#include <ansi.h>

int do_jump(string arg);
int do_plump(string arg);

void create()
{
	set("short", "�ٲ�");
	set("long", @LONG
��������ˮ�����������¡¡�����糱ˮ����һ�㣬̧ͷһ����ֻ
��һ�����ٲ�(pubu)���������ӵ������Ӹ�����ֱк��������������
����(xuanya)��������������������ͷ��
LONG  );
	set("exits", ([ /* sizeof() == 3 */
		"northdown" : __DIR__"road4",
	]));

	set("outdoors", "xiakedao");
	set("item_desc",([
		"���ٲ���"   : "����ϸһ�����ٲ���������г��ڣ����ƺ�������(jump)��ȥ��\n"
		ZJOBACTS2"����ȥ:jump pubu\n",
		"�����¡�" : "��������������ʲôҲ��������ûһ�����������(plump)��ȥ���������̣�\n"
		ZJOBACTS2"����ȥ:plump xuanya\n",
	]));

	setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_plump","plump");
}

int do_jump(string arg)
{
	int n;
	object me;

	me = this_player();
	n = me->query_skill("dodge", 1);
	if (! arg || arg != "pubu")
	{
		write("��Ҫ������������\n");
		return 1;
	}

	message_vision("$N���ٲ�ǰվ�������һ������ͻȻԾ��\n", me);
	if (n >= 80)
	{
		message_vision("ֻ��$N�ż�һ��أ�������ƮƮ��Ծ���ٲ�֮�С�\n", me);
		me->move(__DIR__"yongdao1");
	} else
	if (n >= 50)
	{
		message_vision("ֻ��$Nʹ��ȫ��������������ٿ���ҡҡ�̻̣����������ٲ����档\n", me);
		me->move(__DIR__"yongdao1");
	}
	else
		message_vision("ֻ��$N�߸�Ծ�𣬲����漴���£����������򻹲��Զ�أ�\n", me);

	return 1;
}

int do_plump(string arg)
{
	object ob;

	ob = this_player();

	if (arg != "down" && arg != "xuanya")
	{
		write("��Ҫ��ʲôѽ? \n");
		return 1;
	}

	tell_object(ob,HIR "�㲻��˼�����������������¡�"NOR"\n");
	message("vision", "ֻ��" + ob->name() + "�������������¡�\n",
		environment(ob), ({ ob }));

	if ((int)ob->query_skill("dodge", 1) < 100)
	{
		ob->die();
		return 1;
	}

	ob->move(__DIR__"yadi");
	return 1;
}
