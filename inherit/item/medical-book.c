// medical-book.c

inherit ITEM;

#include <ansi.h>
#include <medical.h>

void setup()
{
	string msg;
	mapping med;
	string *ks;
	int i;

	if (clonep())
		return;

	msg = query("long");
	med = query("can_make");
	if (! mapp(med) || ! sizeof(med))
		return;

	ks = keys(med);
	msg += "���������";
	for (i = 0; i < sizeof(ks); i++)
	{
		if (file_size(MEDICINE(ks[i]) + ".c") < 0)
		{
			log_file("log", "No such medicine:" + MEDICINE(ks[i]) +
				 "\n");
			delete("can_make/" + ks[i]);
			continue;
		}
		if (i) msg += "��";
		msg += MEDICINE(ks[i])->name();
	}
	msg += "�����Ʒ��������ǿ�����ϸ����(read)����ĥһ�¡�\n";
	msg = sort_string(msg, 64);
	set("long", msg);
}

void init()
{
	add_action("do_read", "read");
}

int do_read(string arg)
{
	object me;
	mapping med;
	string skill;
	string m_name;
	string fm_name;
	string *ks;
	int lvl;
	int i;
	int jing_cost;

	if (! arg)
		return notify_fail("��Ҫ��ʲô��\n");

	if (sscanf(arg, "%s from %s", m_name, arg) != 2)
		return notify_fail("�о�����ҩ�read ҩ�� from " +
				   query("id") + "\n");

	if (! id(arg))
		return notify_fail("û���Ȿ�鰡��\n");

	med = query("can_make");
	if (! mapp(med) || ! sizeof(med))
	{
		write(name() + "���沢û�м����κ�ֵ��"
		      "�ر��о������ݡ�\n");
		return 1;
	}

	me = this_player();
	if (me->query("can_make/" + m_name))
	{
		write("���Ѿ�ͨ���ˡ�" + m_name + "�������ܣ�ûʲô���о����ˡ�\n");
		return 1;
	}

	ks = keys(med);
	for (i = 0; i < sizeof(ks); i++)
	{
		if (filter_color(MEDICINE(ks[i])->name()) == m_name)
			break;
	}

	if (i >= sizeof(ks))
	{
		write(name() + "���沢û�м����й�" +
		      m_name + "�����ݡ�\n");
		return 1;
	}

	fm_name = "��" + MEDICINE(ks[i])->name() + "��";
	skill = query("skill/name");
	lvl = (int)me->query_skill(skill, 1);
	if (! lvl)
	{
		write("�����ڶ�" + to_chinese(skill) + "����"
		      "һ�ϲ�ͨ����ô�о������ף�\n");
		return 1;
	}

	jing_cost = med[ks[i]] / 2 + 50;
	if (jing_cost > me->query("jing"))
	{
		me->set("jing", 0);
		write("����������ھ��񲻼ã������о��й�" +
		      fm_name + "��֪ʶ��\n");
		return 1;
	}

	me->receive_damage("jing", jing_cost);

	if (lvl < (int)med[ks[i]])
	{
		write("�����" + fm_name + "ʵ����"
		      "̫�����ˣ�����Ŀǰ��" + to_chinese(skill) +
		      "��ѧʶ���»�����Ū���ס�\n");
		return 1;
	}

	if (random(lvl) < (int)med[ks[i]])
	{
		write(random(2) ? "���о���һ����й�" + fm_name +
				  "�����ݣ���Щ�ջ񣬲�����û�г������ס�\n"
				: "����ϸ�Ķ���һ����й�" + m_name +
				  "�����ݣ������˲������а��\n");
		return 1;
	}

	write("��ϸϸ���ж����й�" + fm_name +
	      "�����ݣ����ڻ�Ȼ���򣬳������������еİ��\n");
	write(HIC "��ѧ��������" + fm_name + HIC "�ķ�����\n");
	me->set("can_make/" + m_name, ks[i]);
	return 1;
}
