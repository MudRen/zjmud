#include <ansi.h>

void init()
{
	if (! interactive(this_player()))
		return;

	switch (NATURE_D->query_month())
	{
	case 12: case 1: case 2: case 3: case 4: case 5:
		remove_call_out("cold_effect");
		call_out("cold_effect", 4);
		break;
	}
}

void do_cold(object me, int scale, int con)
{
	int damage;
	int hour;
	string msg;

	hour = NATURE_D->query_hour();
	if (! con)
	{
		con = me->query_con();
		con = con / 2 + random(con);
	}
	damage = 35 - (con + me->query_temp("apply/warm") + query_temp("warm"));
	if (me->query("born") == "��������") damage -= 25;
	if (damage < 0) damage = 0;
	if (hour <= 6 || hour >= 18) damage += damage / 2;
	if (hour <= 4 || hour >= 22) damage += damage / 2;
	if (hour >= 11 && hour <= 13) damage -= damage / 2;
	damage *= scale;
	if (damage) me->receive_damage("qi", damage);
	if (damage > 80)
		msg = HIB "һ�ɴ̹ǵĺ��紵������ֻ���û���"
		      "��ѪҺ���챻��ס�ˣ�"NOR"\n";
	else if (damage > 60)
		msg = HIB "һ�ɴ̹ǵĺ��紵������ֻ���û���"
		      "�ǳ���Ӳ��"NOR"\n";
	else if (damage > 40)
		msg = HIB "һ�ɴ̹ǵĺ��紵������ֻ��������"
		      "͸���������˽���������û�а��������"NOR"\n";
	else if (damage > 20)
		msg = HIB "һ�ɴ̹ǵĺ��紵������ֻ�����˶�"
		      "Ҫ��ľ�ˣ�"NOR"\n";
	else if (damage > 10)
		msg = HIB "һ�ɴ̹ǵĺ��紵������ֻ��������"
		      "�ǳ����䣡"NOR"\n";
	else if (damage > 0)
		msg = HIB "һ�ɴ̹ǵĺ��紵������о����е�"
		      "�䣡"NOR"\n";
	else
		msg = HIC "һ�ɴ̹ǵĺ��紵�������������ϻ�"
		      "��ͦů�͵ġ�"NOR"\n";

	if (me->query("qi") < 50 && damage > 10)
		me->apply_condition("ill_dongshang",
			me->query_condition("ill_dongshang") + 5 + damage / 3);
	tell_object(me, msg);
}

void cold_effect()
{
	object *ob;
	object cloth;
	int con;
	int damage;
	int i;

	remove_call_out("cold_effect");
	ob = filter_array(all_inventory(), (: userp :));
	if (! sizeof(ob)) return;
	call_out("cold_effect", 4 + random(3));

	for (i = 0; i < sizeof(ob); i++)
	{
		con = ob[i]->query_con();
		con = con / 2 + random(con);
		do_cold(ob[i], 1, con);
	}
}

int valid_leave(object me, string dir)
{
	if (! interactive(me))
		return ::valid_leave(me, dir);

	switch (NATURE_D->query_month())
	{
	case 12: case 1: case 2: case 3: case 4: case 5:
		do_cold(me, 3, 0);
		break;
	}
	return ::valid_leave(me, dir);
}

