// idle.c ������

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	int lvl;
	int n;

	if (me->ban_say(0))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ���ĸ���ҷ�����\n");

	if (sscanf(arg, "%s %d", arg, n) != 2)
		n = 1;

	if (! objectp(ob = find_player(arg)) || ! me->visible(ob))
		return notify_fail("��Ҫ���ĸ���ҷ�����\n");

	if (n < 1)
		return notify_fail("��Ҫ�ñ��˷�����ã�\n"); 

	if (time() - me->query_temp("last/idle") < 10)
		return notify_fail("�����Ҫ����ʹ�÷����񹦣���ʹ��idle <���> <����>\n");

	if (me == ob)
		return notify_fail("�������ˮ��\n");

	if (wizardp(ob))
		return notify_fail("��ķ����񹦵ȼ���û����ô�ߡ�\n");

	if (ob->query("env/no_idle"))
		return notify_fail("�㲻��������˷���...\n");

	lvl = me->query_skill("idle-force", 1);
	if (! lvl)
		return notify_fail("�����ѧ���˷�������˵��\n");

	if (lvl < 50)
		return notify_fail("��ķ�����ˮƽ̫��޷�ʩչ������\n");

	if (lvl < 300 && environment(ob) != environment(me))
		return notify_fail("��ķ�����ˮƽ���ޣ��޷�ʩչ������ǧ��֮�⣡\n");

	if (me->query("jing") < 10 * n)
		return notify_fail("��ľ���̫�����ʩչ��һ�����񹦡�\n");

	if (me->query("learned_points") + n > me->query("potential"))
		return notify_fail("���Ǳ�ܲ������޷�ʩչ��һ�����񹦡�\n");

	me->set_temp("last/idle", time());

	me->receive_damage("jing", 10 * n);
	me->add("learned_points", n);

	message_vision(HIM "$N" HIM "���������дʣ�!@#$%^&��ʲô��˼��\n", me);
	if (random(lvl * lvl) + lvl * lvl < ob->query("combat_exp") ||
	    random(lvl) + lvl / 2 < ob->query_skill("idle-force", 1))
	{
		write("û���κ�Ч����������ķ�����ʧ���ˣ�\n");
		return 1;
	}

	switch(random(4))
	{
	case 0:
		message_vision(HIM "���ͻȻ������һ����ͷ����ݺݵĶ���$N"
			       HIM "���ŵ�$P" HIM "Ŀ�ɿڴ���һ�仰Ҳ˵��������"NOR"\n",
			       ob);
		break;
	case 1:
		message_vision(HIM "������ͻȻ�ܳ�����С��һ��ץס$N"
			       HIM "�������ߣ�����ȥ�����ˣ��ŵ�$P"
			       HIM "���°�ĭ���������˹�ȥ��"NOR"\n",
			       ob);
		break;
	case 2:
		message_vision(HIM "һ���˷�Ҳ�Ƶ����˹���������������" +
			       ob->name() + HIM "��" + ob->name() + HIM "��"
			       "��Ĺ�Ʊ�ֵ��ˣ�\n$P"
			       HIM "����һ��ˤ���˵��ϣ���ס�ĳ鴤��"NOR"\n",
			       ob);
		break;
	default:
		message_vision(HIM "��Ȼ�����������Զ������Խ��Խ�죬$N" +
			       HIM "��ʱ��ɫ���ף�˵����������"NOR"\n",
			       ob);
		break;
	}

	if (lvl > 180) lvl = 180;
	lvl *= n;

	if (! ob->ban_say(1))
		CHANNEL_D->do_channel(this_object(), "rumor", "��˵" +
				      me->name(1) + HIM "ʩչ�����񹦣�" +
				      ob->name(1) + HIM "�޹��ܺ���");
	ob->ban_say_until(lvl, "�㱻��ɵ�ˣ�����˵���ϻ���");
	write(HIC "��ķ����񹦳ɹ��ˣ�" + ob->name(1) +
	      HIC "���ڱ��ŵ�˵���ϻ����ˣ�"NOR"\n");

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : idle <���> <����>

���ָ���������ʹĳһ����Ҳ���˵��������ķ����񹦵���
���ټ��Ժ����ʹ��������ǰ����ұ��졣���÷����񹦵ĳɹ�
�����Լ��ķ����񹦵ȼ��ͶԷ��ľ����йأ�ÿʹ��һ�η�����
������ķ�һ��Ǳ�ܺ�һЩ����
 
HELP );
	return 1;
}

