// put.c

#include <config.h>

inherit F_CLEAN_UP;

int do_put(object me, object obj, object dest);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string target, item, where, tmp;
	object obj, dest, *inv, obj2;
	int i, amount;

	if (! arg) return notify_fail("��Ҫ��ʲô�����Ž����\n");

	if (! wizardp(me)) return notify_fail("�����ѱ����Σ�\n");

	if (sscanf(arg, "%s in %s", item, target) != 2)
		return notify_fail("��Ҫ��ʲô������\n");
	 if (sscanf(target,"%s of %s",tmp,where) == 2)
	 {
		target = tmp;
	 }
	 else
	{
		where = "all";
	}
	 if(where != "me" && where != "here")
	 {
		dest = present(target, me);
	       if (! dest || living(dest)) dest = present(target, environment(me));
	 }else
	 if(where == "me")
	{
		dest = present(target, me);
	       if (! dest || living(dest))
			return notify_fail("������û��" + target + "����������\n");		
	}else
	     dest = present(target, environment(me));

	 if(dest == me) return notify_fail("�����Ѿ�������������\n");

	if (! dest || living(dest))
		return notify_fail("����û��" + target + "����������\n");

	if (dest->query("no_get_from"))
		return notify_fail("���ǲ�Ҫ�����˼��ˡ�\n");

	if (sscanf(item, "%d %s", amount, item) == 2)
	{
		if (! objectp(obj = present(item, me)))
			return notify_fail("������û������������\n");

		if (! obj->query_amount())
			return notify_fail( obj->name() + "���ܱ��ֿ���\n");

		if (amount < 1)
			return notify_fail("����������������һ����\n");

		if (amount > obj->query_amount())
			return notify_fail("��û����ô���" + obj->name() + "��\n");
		else
		if (amount == (int) obj->query_amount())
			return do_put(me, obj, dest);
		else
		{
			obj->set_amount((int) obj->query_amount() - amount);
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			if (do_put(me, obj2, dest))
				return 1;
			if (obj2)
			{
				obj->add_amount(amount);
				destruct(obj2);
			}
			return 0;
		}
	}

	if (item == "all")
	{
		inv = all_inventory(me);
		for (i = 0; i < sizeof(inv); i++)
			if (inv[i] != dest)
				do_put(me, inv[i], dest);
		write("Ok.\n");
		return 1;
	}

	if (! objectp(obj = present(item, me)))
		return notify_fail("������û������������\n");
	return do_put(me, obj, dest);
}

int do_put(object me, object obj, object dest)
{
	mixed msg;

	if (! dest->is_container() && ! dest->is_character())
		return notify_fail(dest->name() + "�����������㲻�ܰѶ����Ž�ȥ��\n");

	if (dest->is_character() &&
	    sizeof(filter_array(all_inventory(dest), (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
	{
		return notify_fail(dest->name() + "����Ķ���ʵ��"
			    "��̫���ˣ���û���ٷŶ����ˡ�\n");
	} else
	if (dest->is_container() && sizeof(all_inventory(dest)) >= MAX_ITEM_CARRIED)
		return notify_fail(dest->name() + "����Ķ���ʵ��"
			    "��̫���ˣ����Ⱥú���������ɡ�\n");

	if (! undefinedp(msg = obj->query("no_put")))
	{
		if (! stringp(msg))
			msg = "���������Ҫ�ҷš�\n";
		return notify_fail(msg);
	}

	if (obj->is_corpse())
		return notify_fail("���޷���" + obj->name() + "����ȥ��\n");

	if (playerp(obj))
		return notify_fail("���޷���" + obj->name() + "����ȥ��\n");

	if (obj == dest)
		return notify_fail("��... �Լ����Լ�������뷨�Ƚ���Ȥ��\n");

	if (obj->move(dest))
	{
		message_vision(sprintf("$N��һ%s%s�Ž�%s��\n",
			       obj->query("unit"), obj->name(),
			       dest->name()), me);
		return 1;
	}

	return 0;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : put <��Ʒ����> in <ĳ����>
 
���ָ��������㽫ĳ����Ʒ�Ž�һ����������Ȼ��������Ҫӵ��������Ʒ��
 
HELP );
	return 1;
}
