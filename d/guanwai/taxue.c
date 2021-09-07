// /guanwai/taxue.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "̤ѩԺ");
	set("long", @LONG
����һ����ʯ���̵�С·�������������Ƶģ�ǽ�ڶ���Щ�����ˣ�
����ȥ��Щ���ۣ���������ȴƮ�����������������ǳ�������������
һ���Ե���Щ������СԺ�ӣ��ƺ�ûʲô������ʱ��ʱ��һЩ���ҵ�
���ӴҴҶ�����
LONG );
	set("exits", ([
		"west"  : __DIR__"shizilu",
	]));

	set("outdoor", "guanwai");
	setup();
}

void init()
{
	add_action("do_amble", "amble");
}

int is_valid()
{
	int m = NATURE_D->query_month();

	return (m >= 10 || m <= 2);
}

string long()
{
	string msg;

	if (is_valid())
		msg = "������һ�صĻ�ѩ���㲻�ɵøо��������⡣�붬"
		      "��������ү���²��Ļ�ѩ������û���˴�ɨ������"
		      "�ڵ��ϻ�ѩ�������ϳ�֮�ʱ��ʱ��һЩ���ҵĵ�"
		      "�������Ƶ�ƮȻ̤ѩ(amble) ��Ժ����ͷ������һͷ"
		      "���е�����һЩ��ӡ��Ҳ�����߹�û������㼣����"
		      "��̾�ۡ�\n";
	else
		msg = "Ժ������һ�ص���ʯ�ӣ��Ե���Щ�����������￿��"
		      "һ��ľ���ӣ�����д�ţ�" HIW "̤ѩ�޺ۣ�Ҳ�಻��  ��һ"
		      "��" NOR "����д����Ȼ�ʲ�׾�ӣ�ȴҲ�Ե���������������"
		      "��ͬ��\n";

	return sort_string(msg, 60, 4);
}

int do_amble()
{
	object me;
	int lvl;

	me = this_player();

	if (me->is_busy())
		return notify_fail("������æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("����æ�Ŵ���ء�\n");

	me->start_busy(2 + random(3));
	if (me->query("food") >= me->max_food_capacity() * 9 / 10)
	{
		write("����Ժ�����������Ļ���һȦ�����Ŷ��ӣ����á��Ĵ���һ�����á�\n"
		      "���룺����ٲ��ߣ����ʮ�ţ�\n");
		return 1;
	}

	if (! is_valid())
	{
		write("����Ժ�����������������һȦ������⣬����̫�����ˡ�\n");
		return 1;
	}

	if (me->query("neili") < 100)
	{
		write("�㿴�˿���Ժ�Ļ�ѩ������һ����������Ȼ����������Щ���á�\n");
		return 1;
	}

	me->add("neili", -50 - random(50));
	write("������һ�������ŵ��ѩ����ƮƮ��������ȥ��\n");
	lvl = me->query_skill("taxue-wuhen", 1);
	if (lvl < 50)
	{
		message_vision("$N�λ����Ƶ��������������ۡ���һ�½������"
			       "������ѩ�У�һ����ɥ֮ɫ��\n", me);
		return 1;
	} else
	if (lvl < 100)
	{
		message_vision("$N����ǿǿ������Ժ������һȦ������һ����ǳ"
			       "��һ�Ľ�ӡ���ǵ����˴�Ц��\n", me);
		return 1;
	}

	switch (random(3))
	{
	case 0:
		message_vision("$N����һЦ��˫������̤ѩ���ߣ���"
			       "��Ʈ��֮����\n", me);
		break;

	case 1:
		message_vision("$N��ɫľȻ��ֻ�ǲ�ס������ǰ�У�"
			       "���󼸺�û�����°���ӡ��\n", me);
		break;

	default:
		message_vision("$N�����󲽣�һ���������˳�ȥ����"
			       "һ���������һȦ���Թ�����ڤ��˼����\n", me);
		break;
	}

	if (me->can_improve_skill("dodge"))
		me->improve_skill("dodge", lvl / 4 + random(lvl / 4));

	if (me->can_improve_skill("taxue-wuhen"))
		me->improve_skill("taxue-wuhen", lvl / 4 + random(lvl / 4));
	return 1;
}
