// murongfu.c Ľ�ݸ�

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;

mixed try_learn_sk();

void create()
{
	set_name("Ľ�ݸ�", ({ "murong fu", "murong", "fu" }));
	set("long", @LONG
���ǹ���Ľ�ݵĴ��ˣ���Ľ�ݲ�֮�ӣ���ν��Ľ�ݡ����Ƿ塣
�������Ǻ��Ƿ�������Ľ�ݼҸ��֡�����ò���ţ���ȹ��ˣ�
��ȷ��Ѱ���˿ɱȡ�
LONG );
	set("titile", "����Ľ��");
	set("gender", "����");
	set("age", 25);
	set("shen_type",-1);
	set("attitude", "peaceful");

	set("str", 27);
	set("int", 29);
	set("con", 31);
	set("dex", 28);

	set("qi", 4100);
	set("max_qi", 4100);
	set("jing", 2100);
	set("max_jing", 2100);
	set("neili", 4900);
	set("max_neili", 4900);
	set("jiali", 80);

	set("combat_exp", 1750000);

	set_skill("force", 180);
	set_skill("literate", 120);
	set_skill("cuff", 170);
	set_skill("sword", 170);
	set_skill("dodge", 180);
	set_skill("parry", 190);
	set_skill("zihui-xinfa", 180);
	set_skill("douzhuan-xingyi", 190);
	set_skill("beidou-xianzong", 180);
	set_skill("qixing-quan", 170);
	set_skill("murong-sword", 170);

	map_skill("force", "zihui-xinfa");
	map_skill("dodge", "beidou-xianzong");
	map_skill("cuff",  "qixing-quan");
	map_skill("parry", "douzhuan-xingyi");
	map_skill("sword", "murong-sword");

	prepare_skill("cuff", "qixing-quan");

	create_family("Ľ������", 16, "����");

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 20);
}

void attempt_apprentice(object ob)
{
	if(! permit_recruit(ob))
		return;

	command("nod");
	command("recruit " + ob->query("id"));
	command("say �ú�ѧϰ�书��Ϊ�⸴���Ǵ�����׼����");
	return;
}

