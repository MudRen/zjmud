// zhang.c

#include <ansi.h>

inherit NPC;

int is_punisher() { return 1; }

void create()
{
	set_name("������", ({ "zhang zhaozhong", "zhang", "zhaozhong" }) );
	set("title", "���־�����Ӫ����");
	set("nickname", HIR "�����й�" NOR);
	set("gender", "����");
	set("age", 43);
	set("long", @LONG
�������˳ơ������й١�����Ŀ��࣬��һ�Զ̺��ӡ�����ʢ�ԡ���
��һǹ��Ī��һ�š�����ָ���ˡ������Թ�����»��Ͷ��͢������
������������Щ������������ֱ�ϡ�
LONG );
	set("combat_exp", 1800000);
	set("shen_type", -1);
	set("attitude", "heroism");
	set("max_neili", 5500);
	set("neili", 5500);
	set("max_jing", 2500);
	set("jing", 2500);
	set("max_qi", 5000);
	set("qi", 5000);

	set("str", 35);
	set("int", 32);
	set("con", 33);
	set("dex", 31);

	set_skill("unarmed", 240);
	set_skill("sword", 240);
	set_skill("parry", 240);
	set_skill("dodge", 240);
	set_skill("force", 250);
	set_skill("taiji-shengong", 250);
	set_skill("taiji-jian", 240);
	set_skill("taiji-quan", 240);
	set_skill("tiyunzong", 240);
	map_skill("dodge", "tiyunzong");
	map_skill("force", "taiji-shengong");
	map_skill("sword", "taiji-jian");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");

	create_family("�䵱��", 13, "����");
	setup();

	set_max_encumbrance(100000000);
	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 200);
	set_temp("apply/armor", 200);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.sui" :),
		(: perform_action, "unarmed.zhen" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	carry_object("/clone/weapon/green_sword")->wield();
	carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{
	add_action("do_halt", "halt");
}

int do_halt()
{
	object me;

	if (this_player() == query_temp("catch_ob"))
	{
		write(name() + "�ȵ������㻹��������ǰ������"
		      "�ԹԵ����־��ܰɣ���\n");
		return 1;
	}

	return 0;
}

void fight_ob(object ob)
{
	int damage;

	if (is_fighting(ob))
		return;

	if (ob != query_temp("catch_ob"))
	{
		message_vision(HIY "$N" HIY "��$n" HIY "���"
			       "�����󵨣���Ȼ�ҹ����ٲ����ô��\n"
			       "˵�գ�ֻ��$N" HIY "����һ�ţ���$n"
			       HIY "�ߵ��ڵأ�����"NOR"\n",
			       this_object(), ob);
		damage = 500 + random(100);
		ob->receive_damage("qi", damage, this_object());
		ob->receive_wound("qi", damage / 2, this_object());
		ob->remove_enemy(this_object());
		remove_enemy(ob);
		if (! ob->is_busy())
			ob->start_busy(2);
		return;
	}

	::fight_ob(ob);
	if (! is_killing(ob->query("id")))
		kill_ob(ob);
}

int accept_fight(object ob)
{
	message_vision("$N����Ķ�$n���������й��ɣ����������£�����\n",
		       this_object(), ob);
	return 0;
}

int accept_kill(object ob)
{
	return 1;
}

int accept_hit(object ob)
{
	return 1;
}

void catch_ob(object ob)
{
	remove_enemy(ob);
	message_vision("$N���ְ�$n�������������ȵ������߰ɣ���\n",this_object(), ob);
	message_vision("$N����$nת����ȥ��\n", this_object(), ob);

	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) + HIM "��Ϊ��ɱ�޹������ѱ������й������ؼ��ù鰸��Ѻ����Ρ�");
	ob->get_into_prison(this_object(), "/d/changan/prison", ob->query_condition("killer")/30);
	ob->delete("combat/need_catch");
	ob->clear_condition("killer");
	destruct(this_object());
	return;
}

void start_catch(object ob)
{
	move(environment(ob));
	message_vision("$N���˹���������$n����Ц��һ����\n", this_object(), ob);
	command("chat " + ob->name(1) + "��Ϊ���������ٸ��Ѿ����˺������飬��͹ԹԵĸ��һ�ȥ�ɣ�");

	catch_ob(ob);
}

int attack()
{
	object ob;

	if (objectp(ob = query_temp("catch_ob")) &&
	    ! living(ob) &&
	    environment(ob) == environment())
	{
		catch_ob(ob);
		return 1;
	} else
		return ::attack();
}

void unconcious()
{
	die();
}

void die()
{
	command("chat ���ģ���" + name() + "���Ĺ���������...������û�ã����ǵ���̫ǿ���ˡ�");
	message_vision(HIM "$N" HIM "���¼�����Ѫ������һ��������"
		       HIM "���Ż��������ˡ�\n", this_object());
	destruct(this_object());
}

void scan()
{
	object ob;

	if (! environment())
	{
		destruct(this_object());
		return;
	}

	if (! objectp(ob = query_temp("catch_ob")) ||
	    environment(ob) != environment() ||
	    environment(ob)->query("no_fight"))
	{
		message_vision("$N��ס��ʽ���㬵������ߡ����漴ת����ȥ��\n",
			       this_object());
		destruct(this_object());
		return;
	}

	if (! living(ob))
	{
		catch_ob(ob);
		return;
	}

	if (! is_fighting(ob))
		fight_ob(ob);

	::scan();
}
