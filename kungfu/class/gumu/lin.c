// lin.c �ֳ�Ӣ
// 1998.9 by Lgg

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();

void create()
{
	set_name("�ֳ�Ӣ", ({"lin chaoying", "lin"}));
	set("gender", "Ů��");
	set("age", 42);
	set("long",
		"�����ǹ�Ĺ�ɵĿ�ɽ��ʦ�ֳ�Ӣ����Ȼ�Ѿ�����ʮ���ˣ���֮ȴ\n"
		"����ͬ��ʮ��ͷ����������ȫ���������������һ�Գ��İ��£�\n"
		"ֻ��ϧ��Ե�޷ݣ�ֻ�ö��������Ĺ���ľӡ�\n");
	set("attitude", "friendly");

	set("str", 28);
	set("int", 35);
	set("con", 31);
	set("dex", 33);

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "sword.he" :),
		(: perform_action, "sword.he" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.ding" :),
	}));

	set("qi", 5500);
	set("max_qi", 5500);
	set("jing", 2700);
	set("max_jing", 2700);
	set("neili", 6800);
	set("max_neili", 6800);
	set("jiali", 100);

	set("combat_exp", 2700000);
	set("score", 0);

	set_skill("force", 280);
	set_skill("yunv-xinfa", 280);
	set_skill("sword", 270);
	set_skill("yunv-jian", 270);
	set_skill("quanzhen-jian", 270);
	set_skill("dodge", 250);
	set_skill("yunv-shenfa", 250);
	set_skill("parry", 270);
	set_skill("unarmed",250);
	set_skill("meinv-quan", 250);
	set_skill("strike", 250);
	set_skill("fireice-strike", 250);
	set_skill("tianluo-diwang", 250);
	set_skill("whip", 240);
	set_skill("yinsuo-jinling", 240);
	set_skill("literate", 180);
	set_skill("taoism", 240);
	set_skill("medical", 270);
	set_skill("yunv-xinjing", 270);
	set_skill("throwing", 260);
	set_skill("yufeng-zhen", 260);

	map_skill("force", "yunv-xinfa");
	map_skill("sword", "yunv-jian");
	map_skill("dodge", "yunv-shenfa");
	map_skill("parry", "meinv-quan");
	map_skill("unarmed", "meinv-quan");
	map_skill("strike", "tianluo-diwang");

	prepare_skill("unarmed", "meinv-quan");
	prepare_skill("strike", "tianluo-diwang");

	create_family("��Ĺ��", 1, "��ɽ��ʦ");

	set("book_count",1);
	set("inquiry", ([
		"������" :  "�󵨺�С�ӣ�Ҳ��ֱ��������ʦ֮����\n",
		"������ʦ" : "������ȫ��̵��ƽ̣��Ժš������ˡ���\n",
		"��Ĺ��" :  "�ǰ������������һ�ִ��µĹ�Ĺ��\n",
		"��Ů�ľ�" : (: ask_yunv :),
		"�����" : "�����û�У������ҡ�",
	]));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.he" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "unarmed.you" :),
		(: perform_action, "strike.wang" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/qingyi")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob) )
		return;

	if (ob->query_int() < 35) {
		command("say �ҹ�Ĺ�ɵĹ����һ�����֣�������ʲ�����");
		return;
	}

	if ((int)ob->query_skill("yunv-xinfa", 1) < 100 ) {
		command("say �����Ů�ķ������,�������Ը�������书��");
		return;
	}

	command("say �ðɣ�����Ҳ���������ˣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

string ask_yunv()
{
	object ob;
	object me;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "�뱾�ɺ��޹ϸ𣬺��������ɵ��ľ���";

	if (me->query_skill("yunv-xinfa", 1) < 55)
		return RANK_D->query_respect(this_player()) +
			"����Ů�ķ����̫ǳ���Ҳ��ܽ���Ů�ľ�������";

	if (query("book_count") < 1)
		return "�������ˣ����ɵ���Ů�ľ��Ѿ�����ȡ���ˡ�";
	add("book_count", -1);
	ob = new("/clone/book/yunvjing2");
	ob->move(me, 1);
	return "�ðɣ��Ȿ����Ů�ľ������û�ȥ�ú��ж���";
}

void reset()
{
	set("book_count", 1);
}
