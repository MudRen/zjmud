#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
	set_name(CYN "���콣" NOR, ({ "yitian sword" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIY "�������������������������Ƶ����콣��\n�ഫ�õ����Կ�(duikan)���Եõ������������ؼ���"NOR"\n");
		set("no_sell", "����������������\n");
		set("no_give", 1);
		set("no_put", 1);
		set("rigidity",8000);   
		 set("icon","05060");   
		set("material", "steel");
		set("wield_msg", HIW "ֻ����ಡ���һ���ƿ����죬�ų����µ�һ��������콣�ѱ�$N�������С�"NOR"\n");
		set("unwield_msg", HIW "$N�����콣������䣬����ֽ����ų���â��"NOR"\n");
	}
	init_sword(210);
	setup();
}
void init()
{
	object me = this_player();

	if (!query("clone") && me)
	{
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("��˵%s�������������%s��", me->name(1), this_object()->name()));
		set("clone", time());
		call_out("move_ob2", 7200);
	}
}
void move_ob2()
{
	object ob;
	object me;
	
	me = environment();
	if (! objectp(me))
		return;

	while (objectp(environment(me)) && ! playerp(me))
		me = environment(me);
		
	if (playerp(me)) {
		if (me->is_fighting())
		{
			call_out("move_ob1", 3);
			return;
		}
		if (ob = present("yitian sword", me)) {
			message_vision("ֻ��$n����һ����â����$N���Ϸɳ���ٿ�������ˣ�\n", me, ob);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("��˵��������%s��%s������ʧ�ˣ�", ob->name(), me->name(1)));
		}
	}
	destruct(ob);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int pro;
	int dam;
	dam = (int) me->query("dex");
	victim->add("neili", -dam * 10);

	if (victim->query("neili") < 0) 
	victim->set("neili", 0); 

	return HIW "���콣Я���쬴̹Ƿ�����ֱֱ����$n��$nֻ�е�ȫ���������һ˿˿���Ž���ӿ����"NOR"\n";
}

