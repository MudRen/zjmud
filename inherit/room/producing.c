// inherit: producing.c

// �̳з��ݱ�����д�����ݸ�ʽ��
// product -+ mineral1 +-- name : ĳ��Ʒ
//	  |	  +-- rate : ������
//	  |	  +-- max  : ���
//	  |	  +-- cost : ����ʱ���ĵ���Դ����
//	  |
//	  + mineral2 +-- ...
//	  ..

#include <ansi.h>

inherit ROOM;

void start_heart_beat()
{
	// ÿ��(MUD��λ)����һ��
	set_heart_beat(120);
}

void setup()
{
	mapping product;
	string mine;
	int count;

	// ����ķ��䲻��ս������������ͣϢ��ת
	set("no_fight", 1);
	set("no_clean_up", 1);

	::setup();

	product = query("product");
	if (! mapp(product))
		return;

	foreach (mine in keys(product))
	{
		// ��������Ĳ�Ʒ
		count = product[mine]["max"] / 10;
		count = count / 2 + random(count);
		set_temp("stored/" + mine, count);
	}

	start_heart_beat();
}

void init()
{
	add_action("do_info", "info");
}

int query_product_amount(string name, int amount)
{
	return query_temp("stored/" + name);
}

// ���amount < 0���ʾ������Դ
void improve_product_amount(string name, int amount)
{
	mapping m;

	if (! mapp(m = query("product/" + name)))
		// ���ṩ������Դ
		return;

	amount += query_temp("stored/" + name);
	if (amount >= m["max"]) amount = m["max"];
	if (amount < 0) amount = 0;
	set_temp("stored/" + name, amount);
}

void heart_beat()
{
	int count;
	mapping product;
	string mine;
	mapping m;
	int rate;
	string cost;
	int cost_total;
	int eff;

	if (! mapp(product = query("product")))
	{
		set_heart_beat(0);
		return;
	}

	// ������Ʒ
	foreach (mine in keys(product))
	{
		// ÿ����������һЩԭ�ϣ�����һЩ��Ʒ
		if (! mapp(m = product[mine]))
		{
			map_delete(product, mine);
			continue;
		}

		// �����ܹ�����������
		if (! intp(rate = m["rate"]) || rate < 1)
			continue;

		count = rate / 2 + random(rate / 2);
		if (arrayp(m["cost"]))
		{
			foreach (cost in m["cost"])
				if (count > (cost_total = query_temp("stored/" + cost)))
					count = cost_total;

			if (count < 1)
				// ԭ�ϲ��㣬�޷�����
				continue;

			// ����ԭ��
			foreach (cost in m["cost"])
				add_temp("stored/" + cost, -count);
		}

		// �������
		improve_product_amount(mine, count);
	}
}

int do_info(string arg)
{
	mapping product;
	mapping stored;
	string mine;
	mapping m;
	string msg;

	if (arg && arg != "") return 0;

	msg = "��ǰ������Դ����Ϣ��\n";

	if (! mapp(stored = query_temp("stored")) ||
	    ! mapp(product = query("product")))
	{
		write("Ŀǰû���κο����Դ��\n");
		return 1;
	}

	foreach (mine in keys(stored))
	{
		if (! mapp(m = product[mine]))
			continue;

		msg += sprintf("%-8s  �������" HIY "%-6d" NOR,
			       m["name"], stored[mine]);
		if (m["rate"])
			msg += sprintf("  �����ʣ�" HIC "%3d" NOR,
				       m["rate"]);
		msg += "\n";
	}

	write(msg);
	return 1;
}
