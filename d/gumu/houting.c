// houting.c ����
#include <ansi.h>
inherit ROOM;

int do_tang(string arg);
int do_niu(string arg);

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǹ�Ĺ�ĺ������ܷ������ʵʵ��û��һ˿�ķ�϶���ڻ谵
�ĵƹ��£��㷢��ǽ��������һ���� (picture)���ƺ���һ�������
Ф�����������룬�ڷ��ż��߹ײ�(coffin)������ֻ��һ�߹ײĵ�
�װ�û�к��ϣ��ײ��к���տ���Ҳ��
LONG
	);

	set("exits", ([
		"north" : __DIR__"zhengting",
	]));

	set("item_desc", ([
		"������": "������һ�������ʿ�ı�Ӱ��������ʲô��ò��������һ��ָ�죬�������š�" + MAG "��������" NOR + "���������֡�\n",
		"���ײġ�": "�ú���ʯ�����ɵĹײģ��װ���Ϻ󣬾�û��һ˿�ķ�϶�ˡ�\n"
			ZJOBACTS2"�ɽ�ȥ:tang coffin\n",
	]) );

	set("getbook", 1);
	set("valid_startroom",1);

	setup();
}

void init()
{
	add_action("do_tang", "tang");
	add_action("do_niu", "niu");
}

int do_tang(string arg)
{
	object me = this_player();
	object ob;

	if (! arg || arg != "coffin")
	{
		return notify_fail("��Ҫ�����Ķ���\n");
	}

	if (query("getbook") > 0)
	{
		tell_object(me,"���ɽ��ײ��У��ѹװ���ϣ���ʱһƬ�ڰ����ƺ���쳾�����ˣ����������ƺ������װ��ڱ��������֣�ϸϸ����������һͷд�š�"
					+HIY"��Ů�ľ�����ѹȫ�棻����һ������������"NOR+"������ʮ�������֣���һͷ������һЩͼ��֮��ķ��š��㲻֪���ԣ������������"
				"��������˵�������������ϲ�����ϸϸ�ؽ���������ȫ������������\n");
		tell_object(me,"��������֮�䣬���ƺ������׽�����һ��͹��Ļ���(lock)��\n");
		tell_object(me,"���������"ZJURL("cmds:niu lock")+ZJSIZE(15)"Ťһ��"NOR"(niu)���ء�\n");

		ob = new("/clone/book/jiuyin3");
		ob->move(me, 1);
		add("getbook", -1);
	} else
	{
		tell_object(me,"���ɽ��ײ��У��ѹװ���ϣ���ʱһƬ�ڰ����ƺ���쳾���������������ƺ������װ��ڱ���ǰ�������֣��������ּ��Ѿ����˹���ε��ˡ�\n");
		tell_object(me,"ͻȻ�䣬�ƺ������׽�����һ��͹��\n�Ļ���(lock)��\n");
		tell_object(me,"���������"ZJURL("cmds:niu lock")+ZJSIZE(15)"Ťһ��"NOR"(niu)���ء�\n");
	}

	me->set_temp("tmarks/��", 1);
	return 1;
}

int do_niu(string arg)
{
	object me=this_player();

	if (! arg || arg != "lock" || me->query_temp("tmarks/��", 1) < 1)
		return notify_fail("��ҪŤ��ʲô��\n");

	message_vision("$N���ջ��أ���������Ť������Ȼ��׵�֨֨���죬�ѿ���һ���󶴣�$N����������ȥ��\n", this_player());
	me->move(__DIR__"mishi2");

	me->set_temp("tmarks/��",0);
	return 1;
}
void reset()
{
	set("getbook", 1);
}

