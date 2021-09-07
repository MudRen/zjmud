#include <weapon.h>
#include <ansi.h>
inherit BLADE;
inherit F_UNIQUE;
void create()
{
	set_name(CYN "������" NOR, ({ "tulong blade" , "blade" ,"dao", "tulong" }) );
	set_weight(30000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIY "����Ǻų���������������������ĳ������ĵ���������һ�ٶ��֮�ء�\n�ഫ���в��п����Ĵ����ܡ�"NOR"\n");
		set("no_sell", "����������������\n");
		set("no_give", 1);
		set("no_put", 1);
		set("rigidity",8000);   
		set("material", "steel");
		set("wield_msg", HIY "$Nһ����Ц���ӱ������Ǳ��ųơ�"NOR+HIR"��������"NOR+HIY"�������������߸߾���"NOR"\n");
		set("unwield_msg", HIY "$N����һЦ��������������ر���"NOR"\n");
	}
	set("action_list", ([
		"�Կ�" : "duikan yitian sword",
	]));
	init_blade(210);
	setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int pro;
	int dam;
	dam = (int) me->query("str");
	victim->receive_damage("jing",dam * 2);
	return HIM "�������д��Ŵ̶����ƿ�������һ�������磬$nֻ�е��������ң���ǿ�����ֵ���"NOR"\n";
}

void init()
{
	object me = this_player();
	
	add_action("do_open", "duikan");
	if (!query("clone"))
	{
		set("clone", time());
		call_out("move_ob1", 9200);
	}
}
void move_ob1()
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
		
		if (ob = present("tulong blade", me)) {
			message_vision("ֻ��$n����һ����â����$N���Ϸɳ���ٿ�������ˣ�\n", me, ob);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("��˵��������%s��%s������ʧ�ˣ�", ob->name(), me->name(1)));
		}
	}
	destruct(ob);
}

int do_open(string arg, object me)
{
	object pai,ob;
	if(arg != "yitian sword" || !ob = present("yitian sword", environment(this_object()))) 
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	else if (this_player()->query("jiali") <= 200)
	return notify_fail(WHT "\n��������������׼���콣�����Ŀ�����ȥ��"NOR+HIR"\n\nֻ�����ꡱ��һ�����죬�ɽ���������ǡ�"NOR"\n");
	{
		pai = new("/d/tulong/obj/duan1");
		pai->move(this_player());
		pai = new("/d/tulong/obj/duan2");
		pai->move(this_player());

		pai = find_object("/d/tulong/obj/zhenjing");
		if(!pai) pai = load_object("/d/tulong/obj/zhenjing");
		pai->move(this_player());

		pai = new("/d/tulong/obj/miji");
		pai->move(this_player());
		pai = new("/d/tulong/obj/yishu");
		pai->move(this_player());
		message_vision(WHT "\n$N������������׼���콣�����Ŀ�����ȥ��\n"NOR"\n"+HIW"ֻ��һ�����죬$N�ֱ�һ�������������콣�Ѿ����ˡ��㷢�ֵ����о�Ȼ�в��ż����"NOR"\n",this_player());
		destruct (ob);
		destruct(this_object());
		return 1;
	}
}

