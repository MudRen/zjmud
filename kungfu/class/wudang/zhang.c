// zhang.c ������

#include <ansi.h>
#include "wudang.h"

#define ZHENWU_SWORD    "/clone/weapon/zhenwu"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_jian();
mixed ask_me();
mixed ask_tu();

void create()
{
	set_name("������", ({ "zhang sanfeng", "zhang" }));
	set("nickname", HIG "��������" NOR);
	set("long", 
		"�������䵱�ɿ�ɽ���桢�������ֵ�̩ɽ�������������ˡ�\n"
		"��һ���ۻ�Ļ�ɫ���ۣ����ޱ߷���\n"
		"��ĸߴ��������꣬������⣬��ü�԰ס�\n");
	set("gender", "����");
	set("age", 100);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 31);
	set("int", 39);
	set("con", 40);
	set("dex", 32);
	
	set("max_qi", 7500);
	set("max_jing", 5000);
	set("max_jingli", 4000);
	set("jingli", 4000);
	set("max_neili", 9999);
	set("neili", 9999);
	set("jiali", 150);
	set("combat_exp", 3200000);
	set("score", 1200000);

	set_skill("force", 300);
	set_skill("taiji-shengong", 300);
	set_skill("wudang-xinfa", 300);
	set_skill("dodge", 260);
	set_skill("tiyunzong", 260);
	set_skill("unarmed", 290);
	set_skill("taiji-quan", 290);
	set_skill("strike", 290);
	set_skill("wudang-zhang", 290);
	set_skill("hand", 290);
	set_skill("paiyun-shou", 290);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("wudang-jian", 300);
	set_skill("taiji-jian", 300);
	set_skill("blade", 260);
	set_skill("taiji-dao", 260);
	set_skill("taoism", 300);
	set_skill("literate", 180);
	set_skill("medical", 270);
	set_skill("liandan-shu", 270);

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("hand", "paiyun-shou");
	map_skill("strike", "wudang-zhang");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	map_skill("blade", "taiji-dao");

	prepare_skill("unarmed", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 1, "��ɽ��ʦ");
	set("class", "taoist");

	set("inquiry", ([
		"���佣" : (: ask_jian :),
		"����"   : "����ѧʲô���У�",
		"�����а": (: ask_me :),
		"̫��ͼ"  : (: ask_tu :),
	]));

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.sui" :),
		(: perform_action, "unarmed.tu" :),
		(: perform_action, "unarmed.zhen" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
}

void scan()
{
	::scan();

	if (! query_temp("weapon"))
		map_skill("parry", "taiji-quan");
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("wudang-xinfa", 1) < 120)
	{
		command("say ���䵱�����ڼ��书���������ڹ��ķ���"); 
		command("say " + RANK_D->query_respect(ob) + 
			"�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��");
		return;
	}

	if ((int)ob->query("shen") < 60000)
	{
		command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query("combat_exp") < 300000)
	{
		command("say �����ھ�����ǳ��������������书���ȶ���Ҫ����");
		return;
	}

	if (ob->query_skill("taoism", 1) < 120)
	{
		command("say ���䵱���书ȫ�ӵ��������");
		command("say ��Ե����ķ������򻹲�����");
		command("say " + RANK_D->query_respect(ob) + "���Ƕ��о��о���ѧ�ķ��ɡ�");
		return;
	}

	if (ob->query_int() < 32)
	{
		command("say ���䵱���书���迿�Լ�����");
		command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
		command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}

	command("chat ����������������");
	command("chat �벻���ϵ��ڴ���֮�꣬���ٵ�һ������֮�ţ����ǿ�ϲ�ɺء�");
	command("recruit " + ob->query("id"));
}

mixed ask_jian()
{
	object me;
	object ob;
	object owner;

	me = this_player();
	if (me->is_bad())
	{
		if (me->query("family/family_name") == "�䵱��")
			message_vision("$N��ŭ����$n����������Ϊ�䵱���ӣ�"
				       "��������ħ�������������ת����\n",
				       this_object(), me);
		else
			message_vision("$N��ŭ����$n�ȵ�������һ��аħ��"
				       "������Ȼ�ҿ������佣����\n",
				       this_object(), me);
		return 1;
	}

	if (me->query("family/family_name") != "�䵱��")
		return "���佣�������䵱����֮�������������ʲô��";

	if (me->query("family/master_id") != query("id"))
		return "ֻ���ҵĵ��Ӳ��������佣���㻹����ذɡ�";

	if (me->query("shen") < 60000)
		return "������������������ò������Ҳ��ܰ����佣�����㡣";

	ob = find_object(ZHENWU_SWORD);
	if (! ob) ob = load_object(ZHENWU_SWORD);
	owner = environment(ob);
	while (owner)
	{
		if (owner->is_character() || ! environment(owner))
			break;
		owner = environment(owner);
	}

	if (owner == me)
		return "���佣�������������ô����ô�����������أ�";

	if (objectp(owner) && owner != this_object())
	{
		if (! owner->is_character())
			return "���Ѿ������佣�Ѿ����ȥ�ˡ�";

		if (owner->query("family/master_id") == query("id"))
			return "���佣������" + owner->query("name") +
			       "���У���Ҫ���þ�ȥ�����ɡ�";
		else
			return "���佣��������" + owner->query("name") +
			       "���У���ȥ�����һ����ɡ�";
	}

	ob->move(this_object());
	message_vision("$N���ͷ�������ã����������佣Ҫ����һЩ��"
		       "����������飡��\n", this_object(), me);
	command("give zhenwu jian to " + me->query("id"));
	ob->start_borrowing();
	return 1;
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/taiji-jian/zhenwu"))
		return "�Լ��úö���ϰ�ɣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

	if (me->query("shen") < 120000)
		return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

	if (me->query_skill("taiji-jian", 1) < 180)
		return "���̫����������180������Ҫ��������";

	message_vision(HIY "$n" HIY "΢΢��ף����ּ���һ����֦��$N" HIY
		       HIY "ɨ����$N" HIY "������ƽ�����棬��Ϊ�ɻ�ֻ������һ����\n"
		       "��Ȼ$p" HIY "���ƴ�䣬���ȷǷ����仯���$P"
		       HIY "���һ�������Ҳ�����"NOR"\n",
		       me, this_object());
	command("smile");
	command("say ��������ˣ�");
	tell_object(me, HIG "��ѧ���������а��"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);
	me->set("can_perform/taiji-jian/zhenwu", 1);
	return 1;
}

mixed ask_tu()
{
	object me;

	me = this_player();
	if (me->query("can_perform/taiji-quan/tu") >= 10 )
		return "��ѧ���㶼�Ѿ�ѧ�ˣ��Ժ�Ҫ�Ƽ����ã�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

	if (me->query("shen") < 250000)
		return "������������������û������࣬�Ҳ��ܷ��Ĵ�����У�";

	if (me->query_skill("taiji-quan", 1) < 250)
		return "���̫��ȭ������250������Ҫ��������";

	if (me->query_skill("taiji-shengong", 1) < 300)
		return "���̫���񹦻�����300�����ú����аɣ�";

	if (me->query_skill("taoism", 1) <300)
		return "��ĵ�ѧ�ķ��о��Ļ��������ף�Ҫ�¹����ѧ���ǣ�";

	if (me->query("max_jing") < 1000)
		return "��ľ�������1000�㣬���㴫����̫��ͼ��Ҳ�������á�";

	message_vision(HIY "$n" HIY "���ͷ��˫�����Ữ��һ��Ȧ�ӣ�"
		       "���ϵ������޶����𣬽��������¡�"NOR"\n",
		       me, this_object());
	command("smile");
	command("say �㿴���˶��٣�");

	if (me->query("potential") < me->query("learned_points") + 100)
	{
		write("�㿴�˰��죬û���о���ʲô�µĶ�����������Ǳ�ܻ�������\n");
		return 1;
	}

	me->add("learned_points", 100);

	if (me->add("can_perform/taiji-quan/tu", 1) < 10)
	{
		message_vision(HIY "$N" HIY "����ãã�ĵ��˵�ͷ����˼���á�"NOR"\n", me);
		tell_object(me, HIG "���̫��ͼ����һ������"NOR"\n");
	} else
	{
		message_vision(HIY "$N" HIY "��¶Ц�ݣ�ϲ�������Ѿ�"
			       "�����ˣ���ν���������ʵ���޷ֱ𰡣�\n"
			       "$n" HIY "������Ц�������׾ͺã����׾ͺã��Ժ��������ʹ�ã���ȥ�ɣ�\n",
			       me, this_object());
			       
		tell_object(me, HIG "��ѧ���˵����ܼ�̫��ͼ��"NOR"\n");
		if (me->can_improve_skill("taoism"))
			me->improve_skill("taoism", 160000);
		if (me->can_improve_skill("taiji-shengong"))
			me->improve_skill("taiji-shengong", 160000);
		if (me->can_improve_skill("unarmed"))
			me->improve_skill("unarmed", 160000);
	}

	return 1;
}

int accept_object(object me, object ob)
{
	int r;
	if (r = ::accept_object(me, ob))
		return r;

	if (base_name(ob) != ZHENWU_SWORD)
	{
		command("say ��������ֶ�����ʲô��");
		return 0;
	}

	if (me->query("family/master_id") != query("id"))
		command("say ��л��λ" + RANK_D->query_respect(me) + "�����佣���ء�");
	else
		command("say �ܺã��ܺã�");
	destruct(ob);
	return 1;
}

void unconcious()
{
	die();
}
