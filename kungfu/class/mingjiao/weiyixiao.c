// WeiYiXiao.c
// pal 1997.05.10

#include <ansi.h>
#include "fawang.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

void create()
{
	set_name("韦一笑", ({"wei yixiao", "wei", "yixiao",}));
	set("long",
		"他长得活象是一只青翼大蝙蝠。\n"
		"他的脸色灰扑扑的。\n"
	);

	set("title",HIG "明教" HIC "青翼蝠王" NOR);
	set("level",9);
	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 48);
	set("shen_type", 1);

	set("str", 28);
	set("int", 27);
	set("con", 33);
	set("dex", 38);

	set("max_qi", 4500);
	set("max_jing", 2200);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 100);

	set("combat_exp", 1800000);

	set_skill("force", 200);
    	set_skill("dodge", 230);
    	set_skill("strike", 200);
	set_skill("sword", 200);
	set_skill("parry", 200);
    	set_skill("jiuyang-shengong", 150);
	set_skill("bianfu-bu", 250);
      	set_skill("hanbing-mianzhang", 180);
      	set_skill("literate", 100);

    	map_skill("force", "jiuyang-shengong");
	map_skill("dodge", "bianfu-bu");
    	map_skill("strike", "hanbing-mianzhang");
    	map_skill("parry", "hanbing-mianzhang");

	prepare_skill("strike","hanbing-mianzhang");

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: command("perform xixueqingfu") :),
	}) );
	create_family("明教", 0, "护法法王");
	setup();

	carry_object("/d/mingjiao/obj/baipao")->wear();
}
int recognize_apprentice(object me, string skill)
{
	if ((int)me->query("shen") > 10000)
	{
		command("say 老子平生最讨厌你们这些所谓的侠义人士，"
			"还不快滚！");
		return -1;
	}

	if (skill != "bianfu-bu")
		return 0;
	return 1;
}

