#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIY"��ԯ"NOR+HIW"����"NOR+YEL"��"NOR, ({"xuanyuan dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_value", 0);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(full)") < 240)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();

	me->set_temp("last_eat/dan(full)", time());

	message_vision(HIY "$N����һ����ԯ���ĵ�����Ҳ�о������κ�ƣ����"NOR"\n", me);
	my["jingli"] = my["max_jingli"];
	my["neili"]  = my["max_neili"];
	my["jing"]   = my["max_jing"];
	my["qi"]     = my["max_qi"];
	my["eff_jing"] = my["max_jing"];
	my["eff_qi"]   = my["max_qi"];

	me->start_busy(6);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
