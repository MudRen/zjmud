// trans.c

#pragma save_binary

#include <room.h>
#include <ansi.h>

inherit ROOM;

void init_connections();

// ��ͨҪ�㣬���н�ͨ��Ϣ������ MAP_D �У������������������
// F_DBASE �е� trans �����У�ǰΪ��ȥ�ص㣬��Ϊ�۸�

// ��ʾ���˿͵���Ϣ
string trans_prompt()
{
	string msg;
	mapping trans;
	string to;
	mixed pos;

	if (! mapp(trans = query("trans")) || sizeof(trans) < 1)
		return "��������ά���У���ʱ���ṩ��ͨ����\n";

	msg = "�������ڿ�ͨ��ȥ���µط���ͨ·��\n"
	      "-----------------------------------\n";
	msg += ZJOBACTS2+ZJMENUF(2,2,7,30);
	foreach (to in keys(trans))
	{
		if (! mapp(pos = MAP_D->query_trans_info(to)))
			continue;

		msg += sprintf("%s$br#"WHT"%s"NOR":goto %s",pos["name"] + "[" + to + "]",MONEY_D->price_str(trans[to]),to)+ZJSEP;
	}
	msg += "\n";

	return msg;
}

void setup()
{
	::setup();
	init_connections();
}

// ��ʼ������
void init_connections()
{
	mapping trans;
	mixed   conn;
	mixed   item;
	mapping pos;
	string  here;

	pos = MAP_D->query_trans_info();
	foreach (item in keys(pos))
	{
		if (stringp(pos[item]["room"]) &&
		    find_object(pos[item]["room"]) == this_object())
		{
			// ȷ�����Լ���λ��
			here = item;
			break;
		}
	}

	if (here && arrayp(conn = MAP_D->query_connect_info()))
	{
		trans = ([ ]);
		foreach (item in conn)
			if (item[0] == here)
				trans[item[1]] = item[2];
			else
			if (item[1] == here)
				trans[item[0]] = item[2];
		if (sizeof(trans))
			set("trans", trans);
	}
	set("item_desc/�����ӡ�", trans_prompt());
}

void init()
{
	add_action("do_goto", "goto");
}

int do_goto(string arg)
{
	mixed  pos;
	object me;
	object cart;
	object *obs;
	int pay;

	if (! arg)
		return notify_fail("��Ҫȥ���\n");

	if (undefinedp(pay = query("trans/" + arg)))
		return notify_fail("���������(paizi)����������������ط���\n");

	me = this_player();
	if (me->is_busy())
		return notify_fail("ʲô������æ������˵�ɡ�\n");

	pos = MAP_D->query_trans_info(arg);
	if (! mapp(pos) || ! stringp(pos["name"]))
	{
		write("�����������BUG��BUG����\n");
		return 1;
	}

	if (! stringp(pos["room"]))
	{
		write("�����Ц�������Ǹ��ط�ȥ����Ŷ����\n");
		return 1;
	}

	if (wiz_level(me) > 0)
	{
		write("���Ц������ԭ������ʦ�����㲻���ô����Ȼ��Ҫ��·���ǾͲ���Ǯ�ˡ���\n");
		pay = 0;
	} else
	if (me->query("family/family_name") == "���ϻ���")
	{
		pay = 0;
		write("���������ϣ��������������߰ɣ���������˼������Ǯ����\n");
	} else
	if (me->query("age") <= 14)
	{
		pay = 0;
		write("����ȵ�����СС��;ͳ����ˣ����ˣ��ҾͲ������Ǯ�ˡ���\n");
	} else
	if (me->query_skill("higgling", 1) >= 30)
	{
		pay = pay * 100 / (me->query_skill("higgling", 1) + 100);
		switch (random(5))
		{
		case 0:
			write("����������ҳ����չ���������ϣ����������ۿۣ�\n");
			break;

		case 1:
			write("����������ϰ�����ҵ����˰���\n");
			break;

		case 2:
			write("�������λ�ֵܺã��������ðɣ������ۿ���Σ�\n");
			break;

		case 3:
			write("�����̫���ˣ����˵㣬���˵��Ҿ����ˡ�\n");
			break;

		case 4:
			write("����������Ǽ��£������и��ã����˵�ɡ�\n");
			break;
		}

		pay /= 10;
		pay *= 10;
		if (pay < 10) pay = 10; 
		write("������ε������ðɣ��ðɣ��Ǿ�" + MONEY_D->price_str(pay) +
		      "���ˡ���\n");
	}

	if (pay > 0)
	{
		if (MONEY_D->player_pay(me, pay) != 1)
			return 0;
		message_vision("$N�����ʣ������˵������ʲô��\n", me);
	}

	message_vision("���һ���к���������һ���󳵣�$N"
		       "���˳��ͳ����ˡ�\n", me);
	cart = new("/clone/misc/trans_cart");
	obs = filter_array(all_inventory(),
			   (: $1 == $(me) || $1->query_leader() == $(me) &&
					  ! playerp($1) &&
					  ! $1->is_killing($(me)->query("id")) :));
	obs->move(cart);
	me->start_call_out((: call_other, __FILE__, "arrival", me, cart, pos :), 2);
	return 1;
}

void arrival(object me, object cart, mapping pos)
{
	object *obs;

	if (! objectp(me) || ! objectp(cart))
		return;

	if (environment(me) != cart)
		return;

	obs = filter_array(all_inventory(cart),
			   (: $1 == $(me) || $1->query_leader() == $(me) &&
					  ! playerp($1) &&
					  ! $1->is_killing($(me)->query("id")) :));
	tell_object(me, "�㵽��" + pos["name"] + "�����˳���\n");
	obs->move(pos["room"]);
	message("vision", "֨ѽ֨ѽһ���󳵸��˹������漴�ͼ�" +
			  me->name() + "����������\n",
		environment(me), me);

	if (sizeof(obs = all_inventory(cart)) > 0)
	{
		message("vision", "ֻ��ϡ�ﻩ��һ���죬�ӳ�������һ�Ѷ�������\n",
			environment(me), me);
		obs->move(pos["room"]);
	}

	if (objectp(cart))
		destruct(cart);
}

void reset()
{
	::reset();
	init_connections();
}
