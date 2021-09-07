// ai-laozhe.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "qizong.h"

void create()
{
	set_name("������", ({ "ai laozhe", "ai" }));
	set("title", HIG"��ɽ��ʮ��������"NOR);
	set("long", "�����ǻ�ɽ�ĳ��ϰ����ߡ�һ������"
		    "���ϵ�����������η��\n");
	set("gender", "����");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 31);
	set("int", 35);
	set("con", 31);
	set("dex", 32);
	set("age", 66);

	set("qi", 4800);
	set("max_qi", 4800);
	set("jing", 2400);
	set("max_jing", 2400);
	set("neili", 5200);
	set("max_neili", 5200);
	set("jiali", 70);

	set("combat_exp", 1900000);
	set("score", 70000);

	set_skill("cuff", 190);
	set_skill("force", 210);
	set_skill("blade", 180);
	set_skill("sword", 220);
	set_skill("dodge", 190);
	set_skill("parry", 200);
	set_skill("strike", 190);
	set_skill("zixia-shengong", 210);
	set_skill("huashan-xinfa", 210);
	set_skill("poyu-quan", 190);
	set_skill("fanliangyi-dao", 180);
	set_skill("huashan-sword", 220);
	set_skill("hunyuan-zhang", 190);
	set_skill("feiyan-huixiang",190);
	set_skill("literate", 140);

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "fanliangyi-dao");
	map_skill("blade", "fanliangyi-dao");
	map_skill("sword", "huashan-sword");
	map_skill("strike", "hunyuan-zhang");

	create_family("��ɽ��", 12, "����");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "blade.sanshen" :),
		(: exert_function, "recover" :),
	}) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
	string ob_fam;

	ob_fam = ob->query("family/family_name");
	if (! permit_recruit(ob))
		return;

	if (ob->query_skill("force", 1) < 150)
	{
		command("say �ҿ�����ڹ���ûѧ���ң��ú�������");
		return;
	}

	if ((int)ob->query_skill("sword", 1) < 120)
	{
		command("say ��Ľ�����ûѧ���ң����ȥ���û���������");
		return;
	}

	if ((int)ob->query_skill("huashan-sword", 1) < 150)
	{
		command("say ��ɽ�����Ǳ��ɵ��ӱ��뾫ͨ���似��������"
			"���Ž�����");
		return;
	}

	if ((int)ob->query("shen") < 20000)
	{
		command("say ������������������黹���ò�����");
		return;
	}

	if (ob_fam == "��ɽ����")
	{
		command("say �㿴���㣬Ҳ���˽���֮�����ܺ��ߣ��ú���ϰ�书����Щ������");
		ob->delete("family");
	}

	command("say ���������ˣ���Ҫ�����ǻ�ɽ�ɵ�����");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "fighter")
		ob->set("class", "fighter");
}
