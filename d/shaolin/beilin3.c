// Room: /d/shaolin/beilin3.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit ROOM;

int do_study(string arg);

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ƿ������µĵ������ҡ�������С��ȴҲ�����ȫ��
ʯ��ʯ�Σ�ʯ��ʯ���������ڷŵļ�������Ҳ����ʯ�Ƶġ�
�����ƺ��ܾ���ǰ����������ס�������е�ʯ����ƽ����һ��
������ʯ�壬����������Щʲô��
LONG );
	set("objects",([
		"/clone/book/book-stone" : 1,
	]));
	set("item_desc", ([
		"table" : "����һ�����ʯ��ɵ�ʯ�����������Щ��ֵ�ͼ�Ρ�\n"
		ZJOBACTS2"�ж�:study1 table\n",
	]));
	setup();
}

void init()
{
	add_action("do_study", "study1");
}

int do_study(string arg)
{
	object me;
	string msg;

	me = this_player();

	if (arg != "table")
		return notify_fail("��Ҫ��ʲô��\n");

	if ((int)me->query_skill("literate", 1) < 1)
		return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

	if (me->query_temp("stone_learned"))
		return notify_fail("�㲻���Ѿ����ж����𣿻��ǽ�̤ʵ����������ҪȥͶ��ȡ�ɡ�\n");

	if (me->is_busy()) {
	      call_out("do_lian3", 1, me);
		return notify_fail("����æµ�С�\n");
      }

	if (me->query("jing") < 95)
	{
		write("�����ڹ���ƣ�룬�ȴ��ָ���...\n");
                tell_object(me,ZJFORCECMD("use huxin dan"));
	        call_out("do_lian3", 10, me);
		return 1;
	}

	me->receive_damage("jing", 90);
	msg = "����ר���ж�ʯ���ϵĹŹ�ͼ�Ρ�\n";


		if ((int)me->query_skill("finger", 1) < 100)
		{
			me->improve_skill("finger", 1 + random(me->query("str")*2));
			msg += "�����ʯ����ĥ��һ�ض����ƺ���ָ���е��ĵá�\n";
			me->set_temp("stone_learned", 1);
		}

		if ((int)me->query_skill("claw", 1) < 100)
		{
			me->improve_skill("claw", 1 + random(me->query("str")*2));
			msg += "�����ʯ����ĥ��һ�ض����ƺ���צ���е��ĵá�\n";
			me->set_temp("stone_learned", 1);
		}

		if ((int)me->query_skill("strike", 1) < 100)
		{
			me->improve_skill("strike", 1 + me->query("str")*2);
			msg += "�����ʯ����ĥ��һ�ض����ƺ����Ʒ��е��ĵá�\n";
			me->set_temp("stone_learned", 1);
		}

		if ((int)me->query_skill("cuff", 1) < 100)
		{
			me->improve_skill("cuff", 1 + random(me->query("str")*2));
			msg += "�����ʯ����ĥ��һ�ض����ƺ���ȭ���е��ĵá�\n";
			me->set_temp("stone_learned", 1);
		}

		if ( (int)me->query_skill("hand", 1) < 100)
		{
			me->improve_skill("hand", 1 + random(me->query("int")*2));
			msg += "�����ʯ����ĥ��һ�ض����ƺ����ַ��е��ĵá�\n";
			me->set_temp("stone_learned",1);
		}


	if (! me->query_temp("stone_learned"))
		msg += "�����ʯ����ĥ��һ�ض�������������˵"
		       "��̫��ǳ�ԣ�������˵�Ѻ��������ˡ�\n";

	write(msg);
	call_out("do_lian3", 1, me);
	return 1;
}

void do_lian3(object me)
{
	if (! objectp(me))
		return;
	   me->delete_temp("stone_learned");
         tell_object(me,ZJFORCECMD("exert regenerate")+ZJFORCECMD("study1 table"));
}
