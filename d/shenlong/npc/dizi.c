// dizi.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({"dizi"}));
	set("title", HIY"������"NOR);
	set("long",
		"����һ�������̵��ӣ�����͸��һ��а����\n"
	);

	set("gender", "����");
	set("attitude", "peaceful");

	set("age", 20 + random(30));
	set("shen_type", -1);
	set("str", 25 + random(10));
	set("dex", 25 + random(10));
	set("max_qi", 200);
	set("max_jing", 150);
	set("neili", 200);
	set("max_neili", 200);
	set("jiaji", 5 + random(5));
	set("combat_exp", 10000 + random(10000));

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("sword", 50);
	set_skill("blade", 50);
	set("chat_chance", 3);
	set("chat_msg", ({
"������Ӻ�Ȼ�����е���������ѵ��ʱ�����ģ������˵У����²��ɣ�\n",
"������Ӻ�Ȼ�����е�����־���Ŀɳɳǣ����������ޱ��ף�\n",
"������Ӻ�Ȼ�����е����������������������������ǰ˷���\n",
"������Ӻ�Ȼ�����е����˷����˳�Ӣ����������ͬ���¹⣡\n",
"������������е������������ɸ����������룡\n",
	}) );

	setup();
	carry_object("/d/shenlong/obj/xionghuang")->wield();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

#include "sldizi.h"
