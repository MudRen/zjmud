//dizi4.c ��� by river

#include <ansi.h>
inherit NPC;
int ask_wuguan();
int ask_liguan();
int ask_xuexi1();

void create()
{
	set_name("���", ({ "sun jun","sun","jun", "man" }));
	set("title", "��������ĵ���");
	set("gender", "����");
	set("age", 21);
	set("long", "��������ɽ���ĵ��ӣ���ò�Ͱ���һ�쵽��Ц�Ǻǵġ�\n");
	set("combat_exp", 5000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("unique", 1);

	set_skill("force", 50);
	set_skill("strike", 50);
	set_skill("sword", 50);

	setup();
}
