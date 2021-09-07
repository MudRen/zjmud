// head.c �Դ�

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;
inherit F_CUTABLE;
inherit F_SILENTDEST;

void eat_effect();
int is_head() { return 1; }

void create()
{
	set_name(RED "ͷ­" NOR, ({ "head" }));
	set_weight(1500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 1);
		set("no_sell", "�ҵ���...��...����Ҳ������...��...�ٸ��أ�");
		set("food_supply", 10);
		set("food_remaining", 4);
		set("long", RED "һ����Ѫ���ܵ��׼����뷢ɢ�ң���Ѫ������������"NOR"\n");
	}
	 if( clonep(this_object()) ) call_out("decay", 180, 1);
}

int set_from(object owner)
{
	apply_effect((: eat_effect :));
	set("owner_id",  owner->query("owner_id"));
	set("is_player", owner->query("is_player"));
	set("killed_by", owner->query("killed_by"));
	set("defeated_by", owner->query("defeated_by"));
	set("defeated_by_who", owner->query("defeated_by_who"));
	set("assist", owner->query("assist"));
	set("gender", owner->query("gender"));
	if (! stringp(owner->query("victim_name")))
	{
		set("name", "���õ���ͷ");
		owner->set("name", "���õ���ͷʬ��");
	} else
	{
		set("name", owner->query("victim_name") + "����ͷ");
		owner->set("name", "��ͷʬ��");
	}

	if (owner->query_temp("clawed_by_jiuyin"))
	{
		set_temp("clawed_by_jiuyin", 1);
		set("long", query("long") +
			    "�����Ȼ�����С��������һ̽���պÿ��Բ��롣\n");
	}

	set_name(RED + query("name") + NOR, ({ "head" }));
	return 1;
}

int do_cut(object me, string part)
{
	if (! query("food_remaining"))
		return 0;

	return ::do_cut(me, part);
}

int finish_eat()
{
	set_name(WHT "����ͷ" NOR, ({ "bone" }) );
	set_weight(150);
	set("long", "һ����ɭɭ������ͷ��\n");
	return 1;
}

void eat_effect()
{
	object me;

	me = this_player();
	me->add("combat/eatman", 1);
	if (me->query("shen") > -1000)
		me->set("shen", -1000);
}
void decay(int phase)
{
	string msg;
	object env;

       env = environment();
	//�������������ϣ��������仯
	if(env && env->is_character())
	{
		call_out("decay", 180, phase);
		return;
	}
	switch (phase)
	{
	case 1:
	      set("owner_id", "unknow");
		msg =  name(1) + "��ʼ�����ˣ�����һ�����ŵĶ����\n";
	      delete("victim_name");
	      delete("owner_id");
		set_name(RED "���õ���ͷ" NOR, ({ "head", "ͷ­" }));
		set("long",	"�����ͷ��Ȼ�Ѿ���������һ��ʱ���ˣ���ɢ����һ�ɸ�ʬ��ζ����\n");
		call_out("decay", 20, phase + 1);
		break;
	case 2:
	      delete("parts");
		msg = name(1) + "���紵Ǭ�ˣ����һ������ͷ��\n";
		set_name(HIW "����ͷ" NOR, ({ "bone" }) );
		set("long", "һ����ɭɭ������ͷ��\n");
		call_out("decay", 10, phase + 1);
		break;
	case 3:
		msg = "һ��紵������" + name(1) + "���ɹǻҴ�ɢ�ˡ�\n";
		if( env )
			all_inventory(this_object())->move(env);
	      tell_room(env, msg);
		destruct(this_object());
		return;
	}

	while (env && env->is_character())
		env = environment(env);

	if (env) tell_room(env, msg);
}