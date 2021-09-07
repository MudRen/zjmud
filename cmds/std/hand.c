// drop.c

#include <weapon.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, old;
	object weapon;

	if (! arg)
		return notify_fail("��Ҫ�ó�ʲô������\n");

	if (arg == "none" || arg == "nothing")
	{
		if (! objectp(ob = me->query_temp("handing")))
			return notify_fail("�㱾����ʲô��û���ð���\n");

		message_vision("$N��" + ob->name() + "�ջذ��ҡ�\n", me);
		me->delete_temp("handing");
		return 1;
	}

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

	if (objectp(old = me->query_temp("handing")))
	{
		if (old == ob)
			return notify_fail("�㲻������������\n");

		message_vision("$N�ջ����е�" + old->name() + "��\n", me);
		me->delete_temp("handing");
	}

	if ((ob->query_amount() ? ob->query("base_weight") : ob->query_weight()) > 20000)
		return notify_fail(ob->name() + "̫���ˣ��㵥���ò�ס��\n");

	if (ob->is_character())
		return notify_fail(ob->name() + "��ҲҪ�������ϣ�\n");

	weapon = me->query_temp("weapon");
	if (weapon && (((int)weapon->query("flag")) & TWO_HANDED || me->query_temp("secondary_weapon")))
	{
		// none of two hand is free
		return notify_fail("��˫�ֶ�����������û�а취������" + ob->name() + "�ˡ�\n");
	}

	if (ob->query("equipped"))
		return notify_fail("����װ�������أ�\n");

	me->set_temp("handing", ob);
	message_vision("$N�ó�" + (old && ob->name() == old->name() ? "����" : "") +
			"һ" + (ob->query_amount() ? ob->query("base_unit") : ob->query("unit")) +
			ob->name() + "���������С�\n", me);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : hand <��Ʒ����> | nothing
 
���ָ����������ó�һ������Я������Ʒ����ʱ׼��ʹ�á�
 
HELP );
    return 1;
}
 
