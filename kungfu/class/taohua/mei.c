inherit NPC;
#include <ansi.h>;
void create()
{
	set_name( "÷����" ,({ "mei chaofeng", "mei" }));
	set("title", "�ڷ�˫ɷ");
	set("nickname", HIB"��ʬ"NOR);
	set("gender", "Ů��");
	set("age", 32);
	set("long",
	    "÷�����ǻ�ҩʦΨһ��Ů���ӣ��������ܻ�ҩʦ�۰�����ϧ����ʦ�ֳ�����\n"
	    "������㺣�����͵�ˡ������澭�¾�˽����\n"
	    "����ɫ�����Ϊ�þӺ����Ե���ڣ�ģ��ȴ��Ϊ�����������һ��������Ⱦ�\n"
	    "ͨ�޷���\n");
	set("attitude", "aggressive");
	set("str", 29);
	set("int", 32);
	set("con", 35);
	set("dex", 31);

	set("max_qi", 5200);
	set("max_jing", 26000);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 100);
	set("shen_type", -1);

	set("combat_exp", 1700000);

	set_skill("claw", 180);
	set_skill("strike", 180);
	set_skill("force", 160);
	set_skill("parry", 180);
	set_skill("dodge", 150);
	set_skill("cuixin-zhang", 180);
	set_skill("jiuyin-baiguzhao", 180);
	set_skill("luoying-xinfa", 160);
	set_skill("anying-fuxiang", 150);

	map_skill("force", "bibo-shengong");
	map_skill("parry", "luoying-shenjian");
	map_skill("dodge", "anying-fuxiang");
	map_skill("claw", "jiuyin-baiguzhao");
	map_skill("strike", "cuixin-zhang");

	prepare_skill("claw", "jiuyin-baiguzhao");
	prepare_skill("strike", "cuixin-zhang");

	create_family("�һ���", 2, "�������");
	set("inquiry", ([
	   "��ʬ":     "�����ϵ��˶���ô���ҵģ����²��£�����������",
	   "��а":     "������ʦ���Ĵºš�",
	   "����":     "�������ʦ�����ĸ���֮һ���Ǹ��϶��ס�ڰ���ɽ��",
	   "�ϵ�":     "����ү�ѳ��ҵ�����ȥ�ˣ�������һ�ơ�",
	   "��ؤ":     "��ؤͳ����ԭ��ؤ�������Ϊǿ��",
	   "���߹�":   "���߹��书��ǿ�����ҽ̻������С������ʮ���ƣ��ɺޣ�",
	   "����":     "������ʦ���Ķ�Ů�����ǵ������ԡ�",
	   "����":     "�ߣ��������С�Ӱ�������ʦ�磬�Ҿ�����Ź�����",
	   "�":     "�������ҵ�ͽ�ܣ��������ô��",
	   "÷����":   "��������ô�����ǰ׳հ���",
	   "������":   "�����ҵ�ʦ�磬Ҳ���ҵķ������ϧ��������С�������ˡ�",
	   "��ҩʦ":   "������ʦ����"]) );
	setup();
	carry_object("/clone/cloth/bupao")->wear();
	carry_object("/clone/book/jiuyin2");
}

void attempt_apprentice(object ob)
{
	command("������");
}
