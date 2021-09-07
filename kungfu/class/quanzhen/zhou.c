// zhou.c �ܲ�ͨ

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
int ask_jiuyin();

void create()
{
	object book;

	set_name("�ܲ�ͨ", ({"zhou botong", "zhou"}));
	set("gender", "����");
	set("age", 62);
	set("class", "taoist");
	set("nickname",HIY "����ͯ" NOR);
	set("long", "������ȥ��ü�԰ף�һ���õ�ģ����Ȼ������ȴ͸¶��һ�ɽ��\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 31);
	set("int", 36);
	set("con", 32);
	set("dex", 29);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "strike.ju" :),
	}));

	set("qi", 6200);
	set("max_qi", 6200);
	set("jing", 3100);
	set("max_jing", 3100);
	set("neili", 6500);
	set("max_neili", 6500);
	set("jiali", 50);

	set("combat_exp", 2800000);

	set_skill("force", 280);
	set_skill("quanzhen-xinfa", 280);
	set_skill("xiantian-gong", 280);
	set_skill("sword", 250);
	set_skill("quanzhen-jian",250);
	set_skill("dodge", 260);
	set_skill("jinyan-gong", 260);
	set_skill("parry", 270);
	set_skill("unarmed", 270);
	set_skill("kongming-quan", 270);
	set_skill("strike", 250);
	set_skill("chongyang-shenzhang", 250);
	set_skill("haotian-zhang", 250);
	set_skill("literate", 120);
	set_skill("finger", 250);
	set_skill("taoism", 220);
	set_skill("finger", 260);
	set_skill("zhongnan-zhi", 270);
	set_skill("zuoyou-hubo", 360);

	map_skill("force", "xiantian-gong");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "kongming-quan");
	map_skill("finger","zhongnan-zhi");
	map_skill("strike", "haotian-zhang");
	map_skill("unarmed", "kongming-quan");

	prepare_skill("unarmed", "kongming-quan");

	create_family("ȫ���", 1, "�ƽ�");
	set("title", "ȫ��̵�һ������");

	set("book_count",1);
	set("inquiry", ([
		"ȫ���" :  "��ȫ��������µ����������ڡ�\n",
		"�����澭" : (: ask_jiuyin :),
		"�λ�ү" : "��... �λ�ү���˼��ǻ�ү���Ҳ���ʶ��",
		"����"   : "�㣬��˵ɶ��",
		"����"   : "��...��...�ţ�",
	]));

	set_temp("apply/attack", 50);
	set_temp("apply/dodge", 80);
	set_temp("apply/parry", 80);
	set_temp("apply/unarmed_damage", 30);
	set_temp("apply/damage", 30);

	setup();

	if (clonep())
	{
		book = find_object("/clone/book/jiuyin1");
		if (! book) book = load_object("/clone/book/jiuyin1");
		if (! environment(book))
			book->move(this_object());
	}
		
	carry_object("/d/quanzhen/npc/obj/greenrobe")->wear();
}

int ask_jiuyin()
{
	object me,ob,obj ;
	me = this_player ( ) ;
	obj = find_object("/clone/book/jiuyin1");
	if(obj)
		ob = environment(obj);
	if(ob && ob!=this_object())
	{
		say("����ͯ˵�������澭֮ǰ�������������ֻ��ϧ���������ˣ�������"+ob->query("name")+"���ϣ�\n");
	}
	else
	{
		say("����ͯ˵����Ҫ�����澭��������������ɣ��ٺٺ٣�\n");
	}

	return 1;
}

void attempt_apprentice(object ob)
{
	command("hehe");
	command("inn");
}

int recognize_apprentice(object ob, string skill)
{
	if (! ob->query("can_learn/zhou"))
	{
		message_vision("$Nգգ�۾�������$n������Ц����ͣ��\n",
			       this_object(), ob);
		return -1;
	}

	if (skill != "kongming-quan" &&
	    skill != "zuoyou-hubo" &&
	    skill != "unarmed")
	{
		command("say ��...�����û��ʲô�ý���ģ�");
		return -1;
	}

	return 1;
}

int accept_fight(object ob)
{
	if (ob->query("combat_exp") < 500000)
	{
		message_vision("$N����һЦ����$n�������㻹��"
			       "�ѹ�����������˵�ɣ���\n",
			       this_object(), ob);
		return -1;
	}

	if (is_fighting())
	{
		message_vision("$N��$n�е��������ȱ𼱣��Ҵ�����"
			       "�ܾ��������ģ���\n",
			       this_object(), ob);
		return -1;
	}

	if (query("qi") < 4000 ||
	    query("jing") < 2000 ||
	    query("neili") < 4000)
	{
		message_vision("$Nҡҡͷ��$n������������"
			       "̫���ˣ��Ȼ����˵�ɣ���\n",
			       this_object(), ob);
		return -1;
	}

	if (ob->query("can_learn/zhou"))
	{
		message_vision("$N��$n�������ã������Ǿ����棡��\n",
			       this_object(), ob);
		return 1;
	}

	message_vision("$N��ϲ������...�ã��������������������Ȼ��Ȼ���\n",
		       this_object(), ob);

	competition_with(ob);
	return -1;
}

void win()
{
	object ob;
	if (! objectp(ob = query_competitor()))
		return;

	message_vision("$N���˿�$n���ٺ�Ц���������ˮƽ����"
		       "����������Ҫ�ú��������ú���������\n",
		       this_object(), ob);
	::win();
}

void lost()
{
	object ob;
	if (! objectp(ob = query_competitor()))
		return;

	message_vision("$N��ѽһ����Ĩ��Ĩͷ�ϵĺ���ϲ��������λ" +
		       RANK_D->query_respect(ob) + "������书��������\n"
		       "�����ɣ��Ұ���Ϊʦ���ˣ�����ҵ㹦����������һ��"
		       "����ȭ�������һ���\n��С������������ȤҲ����ѧѧ����ô������\n",
		       this_object(), ob);
	ob->set("can_learn/zhou", 1);
	::lost();
}
