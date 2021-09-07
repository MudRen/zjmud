// duanyanqing.c ������

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("������", ({"duan yanqing", "duan", "yanqing", "qing"}));
	set("gender", "����");
	set("nickname",HIR"�����ӯ"NOR);
	set("age", 45);
	set("long", @LONG
�������Ĵ����֮�ף��˳ƶ����ӯ�Ķ����졣ֻ�������������࣬���ϳ�
���һ����Ƥ��ߣ�ϲŭ����һ˿��¶������ݳ���˫����ϥ���ϣ�ֻ����Ҹ
�µ������������ȴ�������������ɣ����ȳ��˸��죡
LONG );
	set("attitude", "peaceful");
	
	set("str", 28);
	set("int", 35);
	set("con", 31);
	set("dex", 30);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}));

	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 100);

	set("combat_exp", 1800000);

	set_skill("force", 220);
	set_skill("duanshi-xinfa", 220);
	set_skill("cuff", 170);
	set_skill("jinyu-quan", 170);
	set_skill("dodge", 210);
	set_skill("tiannan-step", 210);
	set_skill("parry", 220);
	set_skill("staff", 240);
	set_skill("duanjia-sword", 240);
	set_skill("finger", 240);
	set_skill("sun-finger", 240);

	map_skill("force", "duanshi-xinfa");
	map_skill("finger", "sun-finger");
	map_skill("cuff", "jinyu-quan");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "duanjia-sword");
	map_skill("staff", "duanjia-sword");

	prepare_skill("finger", "sun-finger");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "finger.qiankun" :),
		(: perform_action, "finger.dian" :),
		(: perform_action, "sword.jing" :),
		(: perform_action, "sword.jue" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	setup();

	carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/clone/misc/cloth")->wear();
}
