// zhenjing.c

#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

void setup()
{
}

void init()
{
	add_action("do_du", "yanjiu");
	add_action("do_du", "research");
	add_action("halt_read", "stopread");
}

void create()
{
	set_name(HIY "��" HIW "�����澭" HIY "��" NOR, ({ "jiuyin zhenjing", "zhenjing"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("no_give", 1);
		set("no_sell", 1);
		set("no_put", 1);
		set("long", HIW
	"����һ���ñ�ֽд�ɵ��顣������д�š������澭������Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n"
	"�澭������˴����ơ������׹�צ���׽�͹Ǻͻ�����������������о��о���"NOR"\n", );
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	string skill, book;
	int lv;

	if (! arg)
	{
		write("�о������澭��ָ���ʽ��\n"
		      "research|yanjiu <����> from <�����澭>\n");
		return 1;
	}
	if (arg == "yijin-duangu" || arg == "huanyinbu" ||
	    arg == "cuixin-zhang" || arg == "jiuyin-baiguzhao" ||
	    arg == "jiuyin zhenjing" || arg == "zhenjing")
	{
		write("�о������澭��ָ���ʽ��\n"
		      "research|yanjiu <����> from <�����澭>\n");
		return 1;
	}

	if (sscanf(arg, "%s from %s", skill, book) != 2)
		return 0;

	if (me->is_busy())
	{
		write("��������æ���ء�\n");
		return 1;
	}

	if (me->is_fighting())
	{
		write("���޷���ս����ר�������ж���֪��\n");
		return 1;
	}
/*
	if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}
*/
	if (! id(book))
	{
		write("����û���Ȿ�顣\n");
		return 1;
	}

	if (skill != "yijin-duangu" && skill != "huanyinbu" &&
	    skill != "cuixin-zhang" && skill != "jiuyin-baiguzhao")
	{
		write(HIW "����ԴӾ����澭���о����׽�͹ǣ�yijin-duangu������������huanyinbu����\n"
			  "�����ƣ�cuixin-zhang���Լ������׹�צ��jiuyin-baiguzhao����"NOR"\n",);
		return 1;
	}
/*
	if (me->query_skill("sanscrit", 1) < 199 && me->query_skill("taixuan-gong", 1) < 199)
	{
		write("�������ˮƽ̫�ͣ��޷������澭�������ص����ݡ�\n");	
		return 1;
	}
*/
	if ((int)me->query("combat_exp") < 500000)
	{
		write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
		return 1;
	}

	if ((int)me->query("jing") < 100 || (int)me->query("qi") < 100)
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
	me->start_busy(2);
	call_out("auto_read2",2,me,arg);
		return 1;
	}

	if ((me->query("potential") - me->query("learned_points")) < 10)
		return notify_fail("���Ǳ�ܲ��㡣\n");

	if (skill == "yijin-duangu")
	{
	      if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}
		lv = me->query_skill("yijin-duangu", 1);
		if (! me->can_improve_skill("yijin-duangu", 1))
		{
			write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
			return 1;
		}

		if (lv > 199)
		{
			write("���ж���һ��������Ƿ���������˵�Ķ������"
			      "��̫ǳ�ˣ�û��ѧ���κζ�����\n");
			return 1;
		}

		if (me->query("gender") == "����" && (int)me->query_skill("yijin-duangu", 1) > 49)
			return notify_fail("���޸����ԣ�����������������������׽�͹��ڹ���\n");

		if (me->query("character") == "������" && (int)me->query("yijin-duangu", 1) > 199)
			return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
				   "�������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

		if (me->query("character") == "�ĺ�����" && (int)me->query("yijin-duangu", 1) > 169)
			return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
				   "���ĺ������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

		if (me->query("character") == "���ս�թ" && (int)me->query("yijin-duangu", 1) > 139)
			return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
				   "�����ս�թ�������ƺ�ֻ��ѧ�����̶ֳȡ�\n");
		if (me->query("int") < 26)
			return notify_fail("������׽�͹�����ޱȣ�һʱ������ᡣ\n");

		if ((int)me->query_skill("force", 1) < 100)
			return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�׽�͹��ڹ���\n");

		message("vision", me->name() + "��ר�ĵ��ж������澭��\n",
			environment(me), me);
		me->receive_damage("qi", 100);
		me->receive_damage("jing", 100);
		me->add("learned_points", 10);
		me->improve_skill("yijin-duangu", 10 + random(me->query("int")*2));
		write("����ϸ�ж������澭�����澭�������ص��׽�͹������ĵá�\n");
	}
	else
	if (skill == "huanyinbu")
	{
		lv = me->query_skill("shexing-lifan", 1);
		if (! me->can_improve_skill("shexing-lifan"))
		{
			write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
			return 1;
		}

		if (lv > 199)
		{
			write("���ж���һ��������Ƿ���������˵�Ķ�"
			      "����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
			return 1;
		}

		message("vision", me->name() + "��ר�ĵ��ж������澭��\n",
			environment(me), me);
		me->receive_damage("qi", 100);
		me->receive_damage("jing", 100);
		me->add("learned_points", 10);
		me->improve_skill("shexing-lifan", 10 + random(me->query("int")*5));
		write("����ϸ�ж������澭�����澭�������صĻ������Ṧ�����ĵá�\n");
	}
	else
	if (skill == "cuixin-zhang")
	{
	      if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}
		lv = me->query_skill("cuixin-zhang", 1);
		if (! me->can_improve_skill("cuixin-zhang"))
		{
			write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
			return 1;
		}
		if (lv > 199)
		{
			write("���ж���һ��������Ƿ���������˵�Ķ�"
			      "����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
			return 1;
		}
		message("vision", me->name() + "��ר�ĵ��ж������澭��\n",
			environment(me), me);
		me->receive_damage("qi", 100);
		me->receive_damage("jing", 100);
		me->add("learned_points", 10);
		me->improve_skill("cuixin-zhang", 10 + random(me->query("int")*10));
		write("����ϸ�ж������澭�����澭�������صĴ����������ĵá�\n");
	}
	else
	if (skill == "jiuyin-baiguzhao")
	{
	      if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}
		lv = me->query_skill("jiuyin-baiguzhao", 1);
		if (! me->can_improve_skill("jiuyin-baiguzhao"))
		{
			write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
			return 1;
		}

		if (lv > 199)
		{
			write("���ж���һ��������Ƿ���������˵�Ķ�"
			      "����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
			return 1;
		}
		message("vision", me->name() + "��ר�ĵ��ж������澭��\n",
			environment(me), me);
		me->receive_damage("qi", 100);
		me->receive_damage("jing", 100);
		me->add("learned_points", 10);
		me->improve_skill("jiuyin-baiguzhao", 10 + random(me->query("int")*10));
		write("����ϸ�ж������澭�����澭�������صľ����׹�צ�����ĵá�\n");
	}
	else
	{
		write("�澭���沢û�м�¼��Щ���ܡ�\n");
		return 1;
	}
	call_out("auto_read",1,me,arg);
	me->set_temp("read_zhenjing",1);
	return 1;
}

void auto_read(object me,string arg)
{
	if(!me||!me->query_temp("read_zhenjing"))
		return;
	if(me->is_busy())
	{
		call_out("auto_read",1,me,arg);
		return;
	}
	me->force_me("yanjiu "+arg);
}

void auto_read2(object me,string arg)
{
	if(!me||!me->query_temp("read_zhenjing"))
		return;
	if(me->is_busy())
	{
		call_out("auto_read2",1,me,arg);
		return;
	}
	me->force_me("exert recover");
	me->force_me("exert regenerate");
	me->force_me("fuyong huxin dan");
	me->force_me("yanjiu "+arg);
}

int halt_read()
{
	object me = this_player();
	me->delete("read_zhenjing");
	return 1;
}