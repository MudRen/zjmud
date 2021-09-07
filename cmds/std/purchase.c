// purchase.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int do_purchase(object me, string from, string item, int count, string money);

mapping items = ([
	"sword"    : "/clone/weapon/changjian",
	"blade"    : "/clone/weapon/gangdao",
	"staff"    : "/clone/weapon/gangzhang",
	"club"     : "/clone/weapon/tiegun",
	"hammer"   : "/clone/weapon/hammer",
	"dagger"   : "/clone/weapon/dagger",
	"pin"      : "/clone/misc/pin",
	"whip"     : "/clone/weapon/changbian",
	"throwing" : "/clone/weapon/tielianzi",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string item;
	object ob;
	string from;
	int    count;
	string money;
	int    pay;

	if (! arg)
		return notify_fail("����㹺��ʲô��\n");

	if (sscanf(arg, "%s from %s with %d %s", item, from, count, money) == 4)
		return do_purchase(me, from, item, count, money);

	if (sscanf(arg, "%*s from %*s") == 2)
		return notify_fail("����㻨����Ǯ��\n");

	if (arg == "cancel")
	{
		string target;
		object target_ob;

		if (! stringp(target = me->query_temp("pending/purchase")))
			return notify_fail("�����ڲ�û�д���ͱ��˹���ʲô����\n");

		if (objectp(target_ob = present(target, environment(me))))
			tell_object(target_ob,
				    YEL + me->name(1) + "�������㹺��������ͷ��"NOR"\n");
		tell_object(me, YEL "������˽��׵���ͷ��"NOR"\n");
		me->delete_temp("pending/purchase");
		me->delete_temp("pending/info");
		return 1;
	}

	if (me->query("doing") != "scheme")
		return notify_fail("ֻ���ڼƻ��в���ʹ�������������ߡ�\n");

	if (undefinedp(item = items[arg]))
		return notify_fail("����û���������ֵ��ߡ�\n");

	if (me->is_busy())
		return notify_fail("��������æ��û�չ�����ߡ�\n");

	pay = 10000;
	if (me->query("family/family_name") == "���ϻ���")
		pay = 2000;
	else
		pay = pay * 100 / (me->query_skill("higgling", 1) + 100);
	if (MONEY_D->player_pay(me, 10000 + item->value()) != 1)
		return notify_fail("�����ϵ�Ǯ������û�����˹�����ߡ�\n");

	ob = new(item);
	message_vision("$N����һ�����ӵģ����������㹺��" + item->name() + "��\n", me);
	ob->move(me, 1);
	write("��ɹ�������һ" + ob->query("unit") + item->name() + "��\n");
	me->start_busy(20);
	return 1;
}

int do_purchase(object me, string from, string item, int count, string money)
{
	int     amount;
	object  from_ob;
	object  item_ob;
	object  money_ob;
	object* total_obs;
	int     total;
	int     combined;

	if (sscanf(item, "%d %s", amount, item) != 2)
		amount = 1;

	from_ob = present(from, environment(me));
	if (! objectp(from_ob))
		return notify_fail("����û������ˡ�\n");

	if (from_ob == me)
		return notify_fail("���ֺ����������⣿�����⣬������ﲻ���������һ�����\n");

	if (! playerp(from_ob))
		return notify_fail("�˼��ƺ��������㡣\n");

	if (! interactive(from_ob))
		return notify_fail("�˼�����û������𻰡�\n");

	if (me->query_temp("pending/purchase") == from_ob->query("id"))
		return notify_fail("�����ڵȱ��˻ػ��ء�\n");

	item_ob = from_ob->query_temp("handing");
	if (! objectp(item_ob) || (item != "?" && ! item_ob->id(item)))
		return notify_fail("�˼Ҳ�û������������������\n");

	if (item_ob->is_item_make())
		return notify_fail("����Ǳ������Ƶ���Ʒ����̫�װɡ�\n");

	if (item_ob->query("money_id"))
		return notify_fail("Ǯ��Ҳ����\n");

	if (item_ob->query("no_drop"))
		return notify_fail("�����Ʒ�����������ס�\n");

	if (amount < 1)
		return notify_fail("���������" + item_ob->query("units") +
				   item_ob->name() + "��\n");

	if (! undefinedp(total = item_ob->query_amount()))
		combined = 1;
	else
	{
		string iname;

		iname = base_name(item_ob);
		total_obs = filter_array(all_inventory(from_ob),
					 (: base_name($1) == $(iname) :));
		total = sizeof(total_obs);
		combined = 0;
	}

	if (amount > total)
		return notify_fail("�˼�����û����ô��" + item_ob->name() + "����\n");

	if (count < 1)
		return notify_fail("��Ҫ������Ǯ��\n");

	money_ob = present(money, me);
	if (! objectp(money_ob))
		return notify_fail("�����ϲ�û������Ǯ����\n");

	if (! money_ob->query("money_id"))
		return notify_fail("�����Լ�ӡ��Ʊ��\n");

	if (count > money_ob->query_amount())
		return notify_fail("������û��ô��" + money_ob->name() + "��\n");

	message_vision("$N����" + chinese_number(count) +
		    money_ob->query("base_unit") + money_ob->name() +
		    "��$n����" + chinese_number(amount) +
		    (combined ? item_ob->query("base_unit") : item_ob->query("unit")) +
		    item_ob->name() + "��"NOR"\n", me, from_ob);
	tell_object(from_ob, YEL "��ͬ��(right)���ǲ�ͬ��(refuse)" + me->name(1) +
			     YEL "(" + me->query("id") + YEL ")��Ҫ��"NOR"\n");
	from_ob->set_temp("pending/answer/" + me->query("id") + "/right",
			  bind((: call_other, __FILE__, "do_right", from_ob, me :), from_ob));
	from_ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
			  bind((: call_other, __FILE__, "do_refuse", from_ob, me :), from_ob));
	me->set_temp("pending/purchase", from_ob->query("id"));
	me->set_temp("pending/purchase_info",
		     ([ "item"   : base_name(item_ob),
			"amount" : amount,
			"money"  : money,
			"count"  : count ]));
	tell_object(me, YEL + "����" + from_ob->name(1) + "�����Ҫ��"NOR"\n");
	return 1;
}

int do_refuse(object me, object ob)
{
	if (! objectp(ob))
		return notify_fail("����û���˵���ػ��ˡ�\n");

	if (ob->query_temp("pending/purchase") != me->query("id"))
		return notify_fail("�˼��Ѿ�����������������ˡ�\n");

	ob->delete_temp("pending/purchase");
	tell_object(ob, me->name(1) + "����������������ҵ������������˰ɡ���\n");
	tell_object(me, "��ܾ���" + ob->name(1) + "��Ҫ��\n");
	return 1;
}

int do_right(object me, object ob)
{
	string  item;
	object  item_ob;
	int     amount;
	string  money;
	object  money_ob;
	int     count;
	object* total_obs;
	int     total;
	int     now_items;
	int     combined;
	object  temp_ob;

	if (! objectp(ob))
		return notify_fail("����û���˵���ػ��ˡ�\n");

	if (ob->query_temp("pending/purchase") != me->query("id"))
		return notify_fail("�˼��Ѿ�����������������ˡ�\n");

	item   = ob->query_temp("pending/purchase_info/item");
	amount = ob->query_temp("pending/purchase_info/amount");
	money  = ob->query_temp("pending/purchase_info/money");
	count  = ob->query_temp("pending/purchase_info/count");
	ob->delete_temp("pending/purchase_info");
	ob->delete_temp("pending/purchase");

	if (! stringp(item))
	{
		tell_object(me, "������û���˼Ҹ���Ȥ�Ķ����ˡ�\n");
		tell_object(ob, "�˼������Ѿ�û�������Ȥ�Ķ����ˡ�\n");
		return 1;
	}

	foreach (item_ob in all_inventory(me))
		if (base_name(item_ob) == item)
			break;

	if (base_name(item_ob) != item)
	{
		tell_object(me, "������û���˼Ҹ���Ȥ�Ķ����ˡ�\n");
		tell_object(ob, "�˼������Ѿ�û�������Ȥ�Ķ����ˡ�\n");
		return 1;
	}

	if (item_ob->query("money_id"))
		return notify_fail("Ǯ��Ҳ������\n");

	if (amount < 1)
	{
		tell_object(me, "�㲻֪���˼Ҿ��������" +
				item_ob->name() + "��\n");
		tell_object(ob, "�˼Ҳ�����㾿��Ҫ�����" +
				item_ob->name() + "��\n");
		return 1;
	}

	if (! undefinedp(total = item_ob->query_amount()))
		combined = 1;
	else
	{
		string iname;

		iname = base_name(item_ob);
		total_obs = filter_array(all_inventory(me),
					 (: base_name($1) == $(iname) :));
		total = sizeof(total_obs);
		combined = 0;
	}

	if (amount > total)
	{
		tell_object(me, "����������û����ô��" + item_ob->name() + "�ˡ�\n");
		tell_object(ob, "�˼���������û����ô��" + item_ob->name() + "�ˡ�\n");
		return 1;
	}

	if (count < 1)
	{
		tell_object(me, "�㲻֪���˼���Ҫ������Ǯ��\n");
		tell_object(ob, "�˼Ҳ�֪������Ҫ������Ǯ��\n");
		return 1;
	}

	if (! stringp(money) || ! objectp(money_ob = present(money, ob)) ||
	    ! money_ob->query("money_id") || count > money_ob->query_amount())
	{
		tell_object(me, "�˼���������û��Ǯ�ˡ�\n");
		tell_object(ob, "�˼�ͬ���ˣ���������������û��Ǯ�ˡ�\n");
		return 1;
	}

	if (money_ob->query("base_weight") * count +
	    me->query_encumbrance() > me->query_max_encumbrance())
	{
		tell_object(me, "�����ڽӲ�����ô��" + money_ob->name() + "��\n");
		tell_object(ob, "�˼����ڽӲ�������ô��" + money_ob->name() + "��\n");
		return 1;
	}

	now_items = sizeof(filter_array(all_inventory(ob), (: ! $1->query("equipped") :)));
	if (! combined && amount + now_items > MAX_ITEM_CARRIED ||
	    (combined && now_items >= MAX_ITEM_CARRIED &&
	     ! item_ob->can_combine_to(ob)))
	{
		tell_object(me, "�˼����ڽӲ�����ô��" + item_ob->name() + "��\n");
		tell_object(ob, "�����ϵĶ���̫���ˣ����ڽӲ�����ô��" + item_ob->name() + "��\n");
		return 1;
	}

	tell_object(me, "��ͬ����" + ob->name(1) + "��Ҫ��\n");
	tell_object(ob, me->name(1) + "ͬ�������Ҫ��\n");
	message_vision("$N�ӹ���$n��" + money_ob->name() + "����" +
		       item_ob->name() + "�ݸ���$n��\n", me, ob);

	// �Է�֧��Ǯ
	if (count == money_ob->query_amount())
		money_ob->move(me, 1);
	else
	{
		temp_ob = new(base_name(money_ob));
		temp_ob->set_amount(count);
		money_ob->add_amount(-count);
		temp_ob->move(me, 1);
	}

	// �����ṩ��Ʒ
	if (combined)
	{
		if (amount == item_ob->query_amount())
			item_ob->move(ob, 1);
		else
		{
			temp_ob = new(base_name(item_ob));
			temp_ob->set_amount(amount);
			item_ob->add_amount(-amount);
			temp_ob->move(ob, 1);
		}
	} else
	{
		while (amount--)
			total_obs[amount]->move(ob, 1);
	}

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : purchase [����] <����> [from <���> with <����> <����>]
	   purchase cancel

����ִ�мƻ��Ĺ����У������ͨ������ָ������������Ҫ�ĸ�����
�����ߣ���������ƻ�����Ҫ��

���⣬��Ҳ����ʹ��������ʹ�û���������һ��������ϵ���
Ʒ�������Ʒ�����ǶԷ��������ģ�����(hand)������ġ��������
��������� �� ���ʾ����Է�����Ķ�����Ϊ�˱������������Ӣ
�Ĵ��Ÿ���һЩ����������Ҫ���Ժ����ˣ��������� cancel ��
�����������ͷ��

see also : scheme

HELP );
	return 1;
}
