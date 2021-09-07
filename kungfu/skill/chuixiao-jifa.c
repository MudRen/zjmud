// chuixiao-jifa.c ���＼��

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if (me->query("int") < 24)
		return notify_fail("���������ԣ�������ȫ��ѧʲô���\n");

	return 1;
}

int play(object me, object ob, string arg)
{
	int lvl;
	int i;
	string m_name;

	if (! arg)
		return notify_fail("��Ҫ��ʲô���ӣ�\n");

	if (! (lvl = me->query_skill(arg, 1)))
		return notify_fail("�㲻�ᴵ�������ӡ�\n");

	if (! SKILL_D(arg)->valid_enable("chuixiao-jifa"))
		return notify_fail("��Ҳ�ܵ�������ô��\n");

	lvl += me->query_skill("chuixiao-jifa", 1) / 2;
	m_name = to_chinese(arg);

	if (me->is_busy())
		return notify_fail("��������æ���Ȼ���ٴ���ɡ�\n");

	if (lvl < 15)
	{
		message_vision("$N������������һ��$n�����ֻ"
			       "�Ƿ����˼��¡����ء���������\n",
			       me, ob);
	} else
	if (lvl < 30)
	{
		message_vision("$N����$n�����˼�����������"
			       "һ����Ϳ��\n", me, ob);
	} else
	if (lvl < 60)
	{
		message_vision("$N����$n������Ĵ��˼�����"
			       "����������������̫������\n",
			       me, ob);
	} else
	if (lvl < 90)
	{
		message_vision("$N����$n������һ��" + m_name + "���е�"
			       "�����˼����Ϊ����\n",
			       me, ob);
	} else
	if (lvl < 150)
	{
		message_vision("$N����$n������һ��" + m_name + "����Ϊ"
			       "���ˣ�������ʤ��\n", me, ob);
	} else
	if (lvl < 225)
	{
		message_vision("$N����$n������һ��" + m_name + "������"
			       "���˸п���ǧ������Ͷ�롣\n",
			       me, ob);
	} else
	if (lvl < 300)
	{
		message_vision("$N����$n������һ��" + m_name + "����������"
			       "��������ƺ���һ������ֱ������"
			       "�Σ�����ԡ�\n", me, ob);
	} else
	{
		message_vision("$N����$n������һ��" + m_name + "��������˼"
			       "���������������侳��������ϲ����"
			       "��˷���У���֪��Ӱ��\n",
			       me, ob);
	}
	me->start_busy(3 + random(3));

	SKILL_D(arg)->do_effect(me);
	return 1;
}
