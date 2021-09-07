// gao-laozhe.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "qizong.h"

void create()
{
	set_name("������", ({ "gao laozhe", "gao" }));
	set("title", HIR"��ɽ��ʮ��������"NOR);
	set("long", 
"�����ǻ�ɽ�ĳ��ϸ����ߡ�һ���벻�ں���ģ�����������죬���²��ӻ���\n"
"������׷������ʦ�ְ����ߡ�\n");
	set("gender", "����");
	set("age", 65);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 26);
	set("int", 25);
	set("con", 28);
	set("dex", 25);
	
	set("qi", 4200);
	set("max_qi", 4200);
	set("jing", 2100);
	set("max_jing", 2100);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 60);

	set("combat_exp", 1750000);
	set("score", 60000);

	set_skill("cuff", 180);
	set_skill("force", 180);
	set_skill("blade", 180);
	set_skill("sword", 180);
	set_skill("dodge", 180);
	set_skill("parry", 180);
	set_skill("strike", 180);
	set_skill("huashan-xinfa", 180);
	set_skill("zixia-shengong", 170);
	set_skill("poyu-quan", 160);
	set_skill("fanliangyi-dao", 180);
	set_skill("huashan-sword", 180);
	set_skill("hunyuan-zhang", 160);
	set_skill("feiyan-huixiang",160);
	set_skill("literate", 100);

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "fanliangyi-dao");
	map_skill("blade", "fanliangyi-dao");
	map_skill("sword", "huashan-sword");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

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

	if (ob->query_skill("force", 1) < 120)
	{
		command("say �ҿ�����ڹ���ûѧ���ң��ú�������");
		return;
	}

	if ((int)ob->query_skill("sword", 1) < 100)
	{
		command("say ��Ľ�����ûѧ���ң����ȥ���û���������");
		return;
	}

	if ((int)ob->query_skill("huashan-sword", 1) < 100)
	{
		command("say ��ɽ�����Ǳ��ɵ��ӱ��뾫ͨ���似��������"
			"���Ž�����");
		return;
	}

	if ((int)ob->query("shen") < 10000)
	{
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ��"
			"�ϣ��㻹�ö���Щ����������£�");
		return;
	}

	if (ob_fam == "��ɽ����")
	{
		command("say �㰡��... ����Ҳ���ǽ���֮�����ܺ��ߣ����ˣ�����Ҳ�ա�");
		ob->delete("family");
	}

	command("say �ðɣ��Ҿ��������ˣ�������ǻ�ɽ�ɻ�Ҫ��������Щ��������");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "fighter")
		ob->set("class", "fighter");
}
