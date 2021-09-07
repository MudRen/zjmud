// luban.c ³��
// Written by Doing Lu 1998/11/17
// ³���Ǹ����췿���NPC�� ���ȣ����ȥ³��������Ҫͼֽ��Ȼ���뽨��
// �ĵص����ͼֽ������Ҫ��30�����ϵĻ滭���ɲſ��ԣ��������30��������
// ��³��ѧϰ��Ȼ�����Ҫ��ͼֽ��³�࣬³��ѯ�ʷ��ݵ����ƣ����ܺ�������
// �еķ���������Ȼ����ѯ�ʷ��ݵ����ͣ����ݵ����Ͷ�������roomtype.h���У�
// ����ѯ��ÿ�������������ÿ���������ܳ������ٶ�ʮ���ַ�����������У���
// �������еķ����short ���ɷ����������ɣ�����Ҫ������룬Ȼ��³���¼
// ���е���Ϣ������ʾ��ҵȴ���ʦ��Ȩ����wizard���ϣ�����׼��
//
// ��ʦ���ߺ�³�ദ��³����ʾ��ʦ������ҵ���Ϣ�������ʦ��׼�ˣ��͸�
// ����Ϣ������������ߺ�³�ദ��³����ʾ��ҿ��Խ��������û�б���׼��
// ����ʾԭ�������Ϣ������ҽ�һ���ķ��ã��Ϳ������ɷ����ļ������޸�
// ��ҵĵ�������¼����Ѿ���������������һ��Կ�ף�Ȼ�������¼����Ϣ��
//
// �����Ҷ���Կ�ף����Ե�³�ദ������һ��Կ�ף���������Ҫ����Կ�ף�
// Ҳ������³��Ҫ��
//
// ��������Ҫ������ݣ�������³�����������ȷ�Ϻ�ɾ�����ݵ�����

// ���ɷ��ݵ�˵��
// ��ѡ��÷�������ʱ��³�ཫ��¼��Ҫ����ķ���ԭ�͵������ļ�����Щ�ļ�
// һ��Ҫ��/d/room/XXXX/�ڣ��������ѡ���˶��־ӣ������ļ�����/d/room
// /dule/�ڡ������ɷ����ļ�ʱ��³�ཫ����Щ�ļ�������/data/room/playerid/��
// ͬʱԭ�ͷ��ݱ�����һ�����ڣ�/d/room/xiaoyuan³�ཫ����������滻����
// �ҽ����ĵص㣬����ԭ�ͷ���������һ����xiaoyuan������СԺ��
//
// ����ԭ�ͷ�����һЩ����Ҫ�󣬱���ԭ�ͷ��̳е���ROOM���ͣ�������ķ���
// �̳�PRIVATE_ROOM���ͣ������ԭ�ͷ����ļ��У�inherit ROOM��һ��Ҫ���
// ����/**/������������/* EXAMPLE */������inhert PRIVATE_ROOM֮ǰ��Ҫ��
// //**����������Ϊ³����Զ��Ľ�����/**/����ȥ������ȥ��//**����������
// �⣬�������ŵ�ԭ�ͷ�����������������䣬set ("key", "ROOM_KEY");����
// Ϊ�˸����õķ������Կ�ס�ͬʱԭ�ͷ������������set ("room_owner",
// "ROOM_OWNER")�����͵����á�

// ����Կ�׵�һ��˵��
// ÿ����ҷ���Կ��Ҫ����һ���ļ�����ʵ����ȫ������һ��ͨ�õ�Կ���ļ���
// ÿ��AUTOLOAD��ʱ���Զ��ĸ��£�֮���Բ���ô������ΪΪ��ʹ��ҵķ�����
// ���ܹ�����һ�������ԣ������ڹ��ڷ�ɢ��������һ�������ϴ����Կ�׵�ʱ
// �����ڹ��ڷ�����

// һЩ������˵��
// �������̸ʱ��¼������
// contract/luban	  : ��¼��̸���ݵ�mapping�����¼����ҵ���ʱ����
// contract/luban/room     : ��¼����������Ϣ��mapping
// contract/luban/descs    : ��¼����������mapping
// contract/luban/questing : �����̸״̬ quest_name/quest_id/quest_desc
// contract/luban/value    : ���跿������Ҫ�ļ۸�(��coinΪ��λ)
// contract/luban/position : ���췿�ݵĵص�

// ³���¼������������
// form : ��¼�������ı�
// form/player/player   : �����ߵ�����
// form/player/position : ���뽨���ĵص�
// form/player/room     : ���뽨������������
// form/player/type     : ���뽨�������ʹ���
// form/player/name     : ���ݵ�����
// form/player/id       : ���ݵĴ���
// form/player/status   : ����״̬ - ����/����/�ܾ�
// form/player/time     : �����ʱ��
// form/player/wizard   : ���������ʦ
// form/player/memo     : ��ʦ��д�ı�ע
// form/player/descs    : �����д������

// ����������ݵ��޸�
// private_room/build   : �Ѿ���������
// private_room/position: �������ڵ�λ�ã�����ڴ����ڳ������ļ�·��
// private_room/entry   : ������ڴ����ļ�·��
// private_room/name    : ��������
// private_room/id      : ����ID
// private_room/type    : ������������

// ʵ�ַ���
// ��̸������һ���򵥵��Զ�������״̬�������û������ݽṹ�е�contract/
// luban�ֶΣ�������Ϣ�ĺ�����do_answer�� �����������״̬������յ���
// Ϣ���ַ�������Ҫ�ǵ��ò�ͬ���жϺ������������1���Ѽ�¼�������Ϣ��
// �������0���ʾ���봦�������ֹ��̸������û�����̸����������stop��
// ������Զ�����״̬���û����ݿ��м�¼����̸��Ϣ��

// ���ݴ��
// �׶�1 - ��̸
// ���ݴ����player->contract/luban/���mapping��

// �׶�2 - ����
// ���ݴ����luban->form/player/���mapping��

// �׶�3 - �������
// ���ݴ����player->private_room/���mapping��
// ���ɵ��ļ������/data/room/player/���Ŀ¼��
// ��ҷ��ݵĴ����ļ������/data/room/player/���Ŀ¼��
// �������Ĵ����ļ��������ͬ��Ŀ¼�У�������׺��һ��

// ����ļ�
// inherit::PRIVATE_ROOM(/inherit/room/privateroom.c)
// �����û�����ķ��������е����ԣ���Ҫ����Կ�׿��źʹ����Ʒ
//
// inherit::BUILD_ROOM(/inherit/room/buildroom.c)
// ���ǽ������Ļ��������е����ԣ���Ҫ�ǿ��Լ�¼���ӵĳ��ڣ����޸�LONG����

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

// �����¼�˸�����ʽ����
// ������һ��mapping���飬����ÿһ��mappingָ����һ���ͺŵķ��ݡ� ÿһ��mapping��������
// Ԫ�أ�һ�����֡��������͡����Ƿ����ַ������飺�ַ�������ָ�������ַ�����ӵ�е��ļ���
// files�еı�����һ��������ļ�(���е�/d/room/xiaoyuan�ĳ���)�����򽨷�ʱ����������

// ���⣺type �� name ��������Ϊ�������͵ı�־��ֻ����һ�������ģ���һ����Ӣ�ĵĶ��ѣ�
// �����ձ�����������ݿ��е������ĵ���������name�ֶΡ�

// ע�⣺����³����һ����Ҫ�������ݵ�NPC���ڸĶ�³����ļ�����ܻᷢ��һЩ���⣬��ʱ����
// �����Ĵ����ļ�ɾ����
static mapping *room_example = ({
([      "name"     : "���־�",
	"type"     : "dule",
	"value"    : 20000000,
	"files"    : ([ "xiaoyuan" : "/d/room/dule/xiaoyuan.c",
			"xiaowu"   : "/d/room/dule/dulewu.c" ,
		     ]),
]),
([      "name"     : "�ʺ��",
	"type"     : "caihong",
	"value"    : 70000000,
	"files"    : ([ "xiaoyuan" : "/d/room/caihong/xiaoyuan.c",
			"dating"   : "/d/room/caihong/dating.c",
			"houyuan"  : "/d/room/caihong/houyuan.c",
			"woshi"    : "/d/room/caihong/woshi.c",
		     ]),
]),
([      "name"     : "������",
	"type"     : "panlong",
	"value"    : 800000000,
	"files"    : ([ "dayuan"   : "/d/room/panlong/dayuan.c",
			"qianting" : "/d/room/panlong/qianting.c",
			"zuowei"   : "/d/room/panlong/zuowei.c",
			"youwei"   : "/d/room/panlong/youwei.c",
			"zoudao"   : "/d/room/panlong/zoudao.c",
			"yingke"   : "/d/room/panlong/yingke.c",
			"chashi"   : "/d/room/panlong/chashi.c",
			"yishi"    : "/d/room/panlong/yishiting.c",
			"zuoyanwu" : "/d/room/panlong/yanwu1.c",
			"youyanwu" : "/d/room/panlong/yanwu2.c",
			"zhongting": "/d/room/panlong/zhongting.c",
			"zuoxiang" : "/d/room/panlong/zuoxiang.c",
			"youxiang" : "/d/room/panlong/youxiang.c",
			"houyuan"  : "/d/room/panlong/houyuan.c",
			"chufang"  : "/d/room/panlong/chufang.c",
			"wuchang"  : "/d/room/panlong/lianwu.c",
			"huayuan"  : "/d/room/panlong/huayuan.c",
			"zhulin"   : "/d/room/panlong/zhulin.c",
			"tingtao"  : "/d/room/panlong/tingtao.c",
			"jusuo"    : "/d/room/panlong/jusuo.c",
			"shufang"  : "/d/room/panlong/shufang.c",
			"woshi"    : "/d/room/panlong/woshi.c",
		     ]),
]),

});

#define WIZLEVEL	wiz_level("wizard")     // �ܹ����������ʦ�ȼ�

static string *ban_room_id = ({
	"north",
	"south",
	"east",
	"west",
	"northup",
	"southup",
	"eastup",
	"westup",
	"northdown",
	"southdown",
	"eastdown",
	"westdown",
	"northeast",
	"northwest",
	"southeast",
	"southwest",
	"up",
	"down",
	"enter",
	"out",
});

// �ڲ�����
private int     ask_me();
private int     ask_paper();
private int     ask_drawing();
private int     ask_certosina();
private int     ask_demolish();
private int     ask_rebuild();
private int     ask_modify();
private int     ask_key();
private int     ask_desc();
private int     recognize_apprentice(object me);
private int     accept_object(object me, object ob);
private void    tell_user_status(object me);
private void    luban_say(string msg);
private void    user_say(string msg);
private int     do_answer(string arg);
private int     do_stop();
private int     do_desc(string arg);
private int     do_show(string arg);
private int     do_changename(string arg);
private int     do_changeid(string arg);
private int     do_changetype(string arg);
private int     do_changedesc(string arg);
private int     do_finish();
private int     do_withdraw();
private int     decide_withdraw();
private int     do_destory();
private void    show_desc(mixed player, string arg);
private void    promote_type(object me);
private int     quest_user(object me);
private int     quest_info(object me);
private int     check_name(object me, string arg);
private int     check_id(object me, string arg);
private int     check_type(object me, string arg);
private int     check_legal_name(string name, string position);
private int     check_legal_id(string name, string position);
private mixed   check_legal_type(string type);
private string  obey_description(string desc);
private object  get_object(string file_name);
private int     record_desc(object me, string room_name, string desc);
private void    record_contract(object me);
private int     modify_desc_in_form(string player_id, string room_name, string desc);
private string  sort_desc(mixed me, string desc);

// ��ʦʹ�õĹ���������صĺ���
private void    show_brief(string player_id);
private int     exist_form();
private int     do_help(string arg);
private int     do_list(string arg);
private int     do_type(string arg);
private int     do_agree(string arg);
private int     do_reject(string arg);
private int     do_delete(string arg);
private void    show_apply();
private void    show_agree();
private void    show_reject();
private void    show_old();
private void    show_all();
private void    show_brief_title();
private void    show_brief_list(string info, string msg);

// ����/��ٷ��ݵ���غ���
private string  file_dir(mixed me);
private string  to_player(string player_id, string file_name);
private void    create_room(object me);

// ��������������ṩ���ⲿ����(/adm/daemons/updated)�����ڸ������
// ������(���ݹ��ϻ��������ɱ����PURGE)
int     demolish_room(object me);

// ����Կ�׵ĺ���
private int     create_new_key(object me);
private object  get_user_key(object me);

mapping* forms;
mapping my_form;	// һ��������������û��ύ�Ľ�����Ϣ

// �����ṩ�ĺ�����֮�����ú궨�壬������Ϊ�˼�С����ʱ�Ŀ���
// ��ѯform
#define query_form(pid, item)	   query("form/" + pid + "/" + item)
// ����form�ڵ�ֵ
#define set_form(pid, item, content)    set("form/" + pid + "/" + item, content)
// �жϸ�����Ƿ����ύ����
#define submit_form(pid)		mapp(query("form/" + pid))

void create()
{
	seteuid(getuid());
	restore();

	set_name("³��", ({ "lu ban", "lu", "luban" }));
	set("title", "���µڶ��ɽ�");
	set("nickname", HIC "����" NOR);
	set("shen_type", 0);
	set("skill_luban",1);
	set("icon","01075");
	set("str", 10000);	      // ��ֹ���յĶ�����������¶�ʧ
	set("int", 60);
	set("gender", "����");
	set("age", 1450);
	set("long",@LONG
����Ǻų����µڶ��ɽ��Ľ�����ʦ����࣬��������ʲô���ӷ��ݣ���
�����¶��������⡣
LONG
);
	set("attitude", "friendly");
	set("inquiry", ([
		"��"  : (: ask_me :),
/*		"����"  : (: ask_me :),
		"ͼֽ"  : (: ask_paper :),
		"��"  : (: ask_demolish :),
		"�ؽ�"  : (: ask_rebuild :),
		"Կ��"  : (: ask_key :),
		"������": (: ask_key :),
		"����"  : (: ask_desc :),
		"�޸���Ϣ": (: ask_modify :), 
		"�滭����": (: ask_drawing :),
		"��Ƕ����": (: ask_certosina :),*/
		 ]));
	
	set_skill("literate",  120);	    // ����д��
	set_skill("drawing",   500);	    // �滭����
	set_skill("certosina", 500);	    // ��Ƕ����

	set("no_teach", ([
		"literate" : "�ҿɲ��ǽ���������",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();

	move("/d/room/xiaoyuan");
	set("startroom", base_name(environment()));
}

// ����ʱ�������
void remove()
{
	save();
}

void init()
{
	object me;
	
	::init();

	if (interactive(me = this_player()))
	{
		remove_call_out("greeting");
		call_out("greeting", 1, me);
	}

	me->delete_temp("decide_withdraw");
	me->delete_temp("demolish_room");

	add_action("do_stop", "stop");
	add_action("do_answer", "answer");
	add_action("do_desc", "desc");
	add_action("do_show", "show");
	add_action("do_changename", "changename");
	add_action("do_changeid",   "changeid");
	add_action("do_changetype", "changetype");
	add_action("do_changedesc", "changedesc");
	add_action("do_finish", "finish");
	add_action("do_finish", "ok");
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "chexiao");
	add_action("decide_withdraw", "decide");
	add_action("do_demolish", "demolish");

	// ������������ʸ��������ʦ�����Ӵ����������
	if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
	{
		add_action("do_help", "help");
		add_action("do_list", "list");
		add_action("do_type", "type");
		add_action("do_agree", "agree");
		add_action("do_reject", "reject");
		add_action("do_delete", "delete");
	}
}

// �����ĵ�
string query_save_file()
{
	return "/data/npc/luban";
}

void greeting(object me)
{
	if (!objectp(me) || environment(me) != environment())
		return;

	// ����ʦ��ʾ����Ϣ
	if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
	{
		if (query("form") && sizeof(query("form")) >= 1)
		{
			message_vision("³���$N�����������ã���������"
				       "Щ������Ҫ�����ء�\n", me);
			tell_object(me, HIG "³������㣺����" HIW "list" HIG "�쿴��" +
					HIW "type" HIG "��ʾ��ϸ��Ϣ��" HIW "agree" HIG +
					"ͬ�⣬" HIW "reject" HIG "�ܾ���" HIW "delete" HIG
					"ɾ������\n	    ʹ��" HIW "help" HIG
					"���Բ鿴���������˵����ʹ�ð�����"NOR"\n");
		} else
			message_vision("³���$N���ͷ����������������ڿΣ�����Զӭ��ʧ���ˣ�\n", me);
		return ;
	} else
	if (query("form/" + me->query("id")))
	{
		tell_user_status(me);
	} else
	// �������ʾ����Ϣ
	if (me->query_temp("contract/luban"))
	{
		message_vision("³���$NЦ������λ" +
			       RANK_D->query_respect(me) +
			       "���ղ���ô̸��̸�ž����ˣ�������"
			       "�⣬���Ǽ���̸�\n", me);
	} else
	switch(random(3)) {
	case 0 :
		message_vision("³���$N˵������λ" +
			       RANK_D->query_respect(me) +
			       "�����ǶԽ�������Ȥ��\n", me);
		break;
	case 1 :
		message_vision("³���$NЦ������λ" +
			       RANK_D->query_respect(me) + "�����߽���"
			       "������û�и����֮����ô�а���\n", me);
		break;
	case 2 :
		message_vision("³���$Nһ���֣�˵������λ" +
			       RANK_D->query_respect(me) +
			       "���ܾ�û��������������\n", me);
		break;
	}
}

// ��֤ѧϰ
int recognize_apprentice(object me)
{
	if (me->query_temp("mark/³��") &&
	    ! me->query_temp("learnd_from/³��"))
	{
		message_vision("³���$N˵���ã����Ȼ����ѧ���Ҿ�"
			       "����һ��ɡ�\n", me);
		me->set_temp("learnd_from/³��", 1);
	}

	me->set_temp("mark/³��", 1);
	return 1;
}

// ������Ʒ��ͼֽ
int accept_object(object me, object ob)
{
	object room;
	object build;	   // �����ĵص�

	if (ob->id("key") && ob->query("item_make"))
	{
		// ������յ���Կ�ף�������
		message_vision("$N��" + ob->name() + "�ݸ���³�࣬³��"
			       "���ͷ���ӹ������ְ����ӵ���һ�ߵ�����"
			       "�\n", me);
		destruct(ob);
		return 1;
	}

	if (ob->query("money_id") && me->query_temp("ask_for_key") &&
	    mapp(me->query("private_room")))
	{
		room = get_object(me->query("private_room/entry"));
		if (! room)
		{
			message_vision("³������ͷ�����յĶ�$N��������ô"
				       "�Ҳ�����ļ��أ����¡�\n", me);
			me->delete_temp("ask_for_key");
			return 0;
		}
			
		if (ob->value() >= 50000)
		{
			message_vision("³������ã�����Կ�׻����Ժ�"
				       "��ǰ��Կ�׿ɾ�ȫ����������\n", me);
			me->delete_temp("ask_for_key");
			if (create_new_key(me));
			{
				destruct(ob);
				return 1;
			}
			return 0;
		} else
		if (ob->value() >= 1000)
		{
			object ko;

			me->delete_temp("ask_for_key");
			ko = get_user_key(me);
			if (ko)
			{
				message_vision("³���ó�һ��Կ�ף��ݸ�"
					       "$N����ŵ��Կ������ˣ�"
					       "������պã�\n", me);
				ko->move(me);				
				destruct(ob);
				return 1;
			}

			message_vision("³���ɻ������֣����Ҳ���Կ��"
				       "��ԭ�ͣ�����һ����ʦ�ɡ�\n", me);
			return 0;
		}
		message_vision("³�࿴�˿�$N��Ǯ����ü���������Ǯ��ʲ"
			       "ôҲ��������\n", me);
		return 0;
	}

	if (ob->id("paper of drawing"))
	{
		if (mapp(me->query("private_room")))
		{
			message_vision("³��Ǻ�Ц����Ī������һ��ס�����ǲ�����\n", me);
			return 0;
		}
		// ����Ϊ�˷�ֹ���ֲ���ȷ��build_room�ı��
		me->delete("private_room");

		if (query("form/" + me->query("id")))
		{
			message_vision("³��Ц�����������㲻���Ѿ��ύ"
				       "������ô��������show�쿴���롣\n", me);
			return 0;
		}
		if (me->query_temp("contract/luban"))
		{
			message_vision("³���ɻ�Ķ�$N˵������ʲô����"
				       "�Ų��Ǹ�������ô��������ʲô��"
				       "�������Ը�����̸(stop)��\n", me);
			return 0;
		}

		if (! ob->query("draw"))
		{
			message_vision("³�࿴��һ�£���$N˵���������"
				       "һ�Ű�ֽ��ʲô����Ҫ�ǲ���ͺ�"
				       "��ѧѧ�滭����(drawing)�ɡ�\n", me);
			return 0;
		}

		if (ob->query("draw/info") == "unknow")
		{
			message_vision("³��ӹ�ͼֽ�����˰��죬��$N��"
				       "�����⻭����ʲô��������Ҫ�ǲ�"
				       "�����ѧѧ�滭����(drawing)��\n", me);
			return 0;
		}

		if (ob->query("draw/type") != "�羰")
		{
			message_vision("³���$N̾������˵�㽨���ð���"
				       "�ط������ҿ����������ڻ�" +
				       ob->query("draw/type") +
				       "������ʲô�ã�\n", me);
			return 0;
		}

		message_vision("³��ӹ�ͼֽ���˿�����$NЦ����"
			       "���Ļ��У��������ɡ�\n", me);		 

		build = get_object(ob->query("draw/info"));
		if (! objectp(build))
		{
			message_vision("³����ϸ���˿���̾�˿���˵����"
				       "�Ǹ��ط����ں����Ѿ���������.."
				       ".\n", me);
			return 0;
		}

		if (! build->is_build_room())
		{
			message_vision("³����ϸ���˿�������������ü��"
				       "��$N˵�����Ǹ��ط������ܽ���"
				       "��...\n", me);
			return 0;
		}

		if (build->query("max_room") &&
		    (int)build->query("max_room") <= build->query_room_count())
		{
			message_vision("³�࿴�����Ժ��˼Ƭ�̣���$N��"
				       "���Ǹ��ط��ķ����Ѿ�̫���ˣ���"
				       "��������˰ɣ�\n", me);
			return 1;
		}

		me->set_temp("contract/luban/position", ob->query("draw/info"));
		destruct(ob);
		quest_user(me);
		return 1;
	}

	// �����Ƿ���д�˱�
	if ((ob->query("money_id") || ob->id("fee free card")) &&
	    mapp(query("form/" + me->query("id"))))
	{
		int value;

		if (query("form/" + me->query("id") + "/status") != "ͬ��")
		{
			message_vision("³��ҡҡͷ����$N������ʦ��û��"
				       "��׼������룬������ذɡ�\n", me);
			return 0;
		}

		value = query("form/" +me->query("id") + "/value");
		if (ob->query("money_id") && ob->value() < value)
		{
			message_vision("³��ӹ�" + ob->name() + "����"
				       "�࣬��$N�Ǻ�Ц��"
				       "����Ǯ�ƺ������ɣ�\n", me);
			return 0;
		}

		if (ob->id("fee free card") &&
		    ob->query("fee free") < value)
		{
			message_vision("³��ӹ���ѿ�����һ�����$NЦ"
				       "�������Ǳ�Ǹ�������⿨��������"
				       "����䷿��\n", me);
			return 0;
		}

		message_vision("³��ӹ�" + ob->name() + "����$N����"
			       "�ã����Ͼͺã�\n", me);
		destruct(ob);
		create_room(me);
		return 1;
	}

	// �����Ƿ�������
	if (ob->query("money_id") || ob->id("fee free card"))
	{	       
		if (me->query_temp("contract/luban/questing") != "quest_desc")
		{
			message_vision("³��΢΢һЦ����$N������ʲô��"
				       "ô�������Ҳ����޹�֮»��\n", me);
			return 0;
		}
		if (ob->value() < 50000 && ! ob->id("fee free card"))
		{
			message_vision("³���Ȼ��Ц����$N���������ƽ�"
				       "�㶼��ϧ���ߺߣ���������������"
				       "����Ҳ�����ۿۡ�\n", me);
			return 0;
		}
		message_vision("³��ӹ�" + ob->name() + "�������е���"
			       "�࣬����Ķ�$N˵�����ܺã��Ҿ͸����¼"
			       "�ڰ�������������Ϣ��һ��֪ͨ�㡣\n", me);
		record_contract(me);
		me->delete_temp("contract");

		if (ob->id("fee free card"))
		{
			message_vision("³���ֵ���������ѿ��������Ű�"
				       "��������ʱ���ٸ��ҡ�\n", me);
			return -1;
		} else
		{
			destruct(ob);
			return 1;
		}
	}
	message_vision("³��ڰ��֣���$N�����㻹���Լ����Űɣ��ҿ��ò��š�\n", me);
	return 0;
}

private void tell_user_status(object me)
{
	int value;

	// ������ύ�˱������ݱ���״̬������ʾ��Ϣ
	switch (query("form/" + me->query("id") + "/status")) {
	case "����" :
		luban_say("��ʦ��û�в���������룬Ҫ��鿴����"
			  "���ı�������show��������޸Ŀ������ҡ�\n");
		break;

	case "�ܾ�" :
		luban_say("������뱻�ܾ��ˣ��������show�鿴��"
			  "�飬������޸Ŀ������ҡ�\n");
		break;

	case "ͬ��" :
		value = query("form/" + me->query("id") + "/value");
		if (! value)
		{
			luban_say("��������Ѿ�����׼�ˣ������˼��˼"
				  "����Ǯ���ɽ������鿴��������show��"
				  "������޸Ŀ������ҡ�\n");
		} else
		{
			luban_say("��������Ѿ�����׼�ˣ�����" +
				  MONEY_D->price_str(value) +
				  "���ɽ������鿴��������show�������"
				  "�޸Ŀ������ҡ�\n");
		}
		break;
	}
}

// �����µ�Կ��
private int create_new_key(object me)
{
	string key_short;
	string key_file;
	string content;
	string old_id;
	string new_id;
	mixed *file;
	object room;
	int i;
	int n;

	// ������Կ��
	n = 1 + (int)me->query("private_room/key_no");
	if (n <= 1) n = 2;
	key_short = file_dir(me) + "key";
	key_file = key_short + (string) (n % 100);
	content = read_file(key_short + ".c");
	if (! content)
	{
		message_vision("³�����ʼ磬���εĶ�$N�����Ұﲻ�����ˣ�"
			       "Կ�׵�ԭ���Ҳ����ˣ���������ʦ�ɡ�\n", me);
		return 0;
	}

	// ���²�д��Կ�׵��ļ�
	old_id = "1 of " + me->query("id");
	new_id = (string) n + " of " + me->query("id");
	content = replace_string(content, "����ԭ��Կ��", "����" +
				 me->query("name") + "��" +
				 chinese_number(n) + "�����Կ��");
	content = replace_string(content, old_id, new_id);
	rm(key_file + ".c");
	write_file(key_file + ".c", content);

	// �������з��ݶ���
	file = get_dir(file_dir(me) + "*.c", -1);
	if (! sizeof(file))
	{
		message_vision("³�����ʼ磬���εĶ�$N�����Ұﲻ�����ˣ�"
			       "��ķ������Ҳ����ˣ���������ʦ�ɡ�\n", me);
		rm(key_file + ".c");
		return 0;
	}
	for (i = 0; i < sizeof(file); i++)
	{
		if (file[i][1] <= 0)
			// �����ļ�
			continue;

		room = get_object(file_dir(me) + file[i][0]);
		if (! room || ! room->is_private_room())
			// �޷��ҵ�������߶�����˽�з�������
			continue;

		room->restore();
		if (! stringp(room->query("room_key")))
			// �÷��䲻��ҪԿ��
			continue;

		// ������Կ��
		room->set("room_key", new_id);
		room->save();

		// ��ʾ��Ϣ
		message("vision", @LONG
һ������ͯ�������������˹������������ߣ�������������㻹û��
���׹�������ô���£�����"����"���°��������ˣ���Ҳ�Ƶ����ˡ�
LONG, room);

	}

	// ��������Կ�׵���Ϣ
	me->set("private_room/key_no", n);

	clone_object(key_file)->move(me);
	message_vision("³��ӹ�����һ��Կ�׵ݸ�$N��������������Կ�װɣ�"
		       "�������Ͼ͸��㻻����\n", me);

	return 1;
}

// ������ҵ�Կ��
private object get_user_key(object me)
{
	string key_file;
	string content;
	object entry;
	int n;

	key_file = file_dir(me) + "key";
	n = (int)me->query("private_room/key_no");
	if (n > 1) key_file += (string) (n % 100);

	return new(key_file);
}

// �ش��йؽ�������Ϣ
private int ask_me()
{
	object me;
	me = this_player();

	if (mapp(me->query("private_room")))
	{
		message_vision("³����ͷ����$N˵������ô����ס�ÿ���"
			       "�⣿���ǲ����⣬���������ؽ�Ŷ��\n", me);
		return 1;
	}

	if (query("form/" + me->query("id")))
	{
		tell_user_status(me);
		return 1;
	}

	message_vision(@SAY
³��΢һ̾����˵�����뽭����Ů��һ���ݺᣬ������𣬳۳����£���
��û�и����֮���������ˣ������������У���ݼ����մ������������
������ͼֽ���ң����ǵص���ʣ����������������ʽ���Ҹ��㽨��ס����
�������������پ��Ƿ��ꡣ
SAY , me);
	return 1;
}

// �ش��й�ͼֽ����Ϣ
private int ask_paper()
{
	object  me;
	object  ob;

	me = this_player();

	if (is_busy())
	{
		tell_object(me, "³����æ���أ�û��������...\n");
		return 1;
	}

	if (mapp(me->query("private_room")) ||
	    query("form/" + me->query("id")))
	{
		message_vision("³�෭��һ��ֽ���ݸ�$N�����Ը�����ȥ�ɡ�\n", me);
	} else
	{
		message_vision("³����ͷ����$N˵�����ܺã��������ͼ"
			       "ֽ��������Ҫ�����ĵص㣬������(draw)��"
			       "�ظ��ҿ�����\n", me);
	}
	ob = new("/d/room/obj/paper");
	if (objectp(ob))
	{
		message_vision("³�෭�˷����ҵ�һ��ͼֽ���ݸ���$N��\n", me);
		ob->move(me);
	} else
	{
		message_vision("³�෭�˰���Ҳû�ҵ�������һ����˵����"
			       "��ô���£�û���ˣ���ȥ����ʦ���ʰɣ�\n", me);
	}

	start_busy(4);
	return 1;
}

// �ش��йػ滭���ɵ���Ϣ
private int ask_drawing()
{
	message_sort("³���$N˵����Ҫ�뻭�źõ��ͼֽ������"
		     "��滭�����ǲ��еģ�û���������ͻ�����"
		     "������ѧϰ���������⣬��������ѧѧ��\n",
		     this_player());
	return 1;
}

// �ش��й���Ƕ���յ���Ϣ
private int ask_certosina()
{
	message_sort("³���$N˵���������ﲻ������Ƕ�Ļ����"
		     "����������Ȥ�Ļ����ҿ��Խ���һ����Ƕ��"
		     "������\n", this_player());
	return 1;
}

// �������ݵ���Ϣ
private int ask_demolish()
{
	object me;

	me = this_player();
	if (me->query_temp("contract/luban"))
	{
		message_vision("³���$N˵���㲻��Ҫ����ô����ô��û��"
			       "�þ�Ҫ���ˣ�����δ����Ѱ���\n", me);
		return 1;
	}

	if (query("form/" + me->query("id")))
	{
		message_vision("³�����һ������$N������ķ��ӻ�û����"
			       "���أ���Ҫ�ǲ��뽨�ˣ��ͳ���(withdraw)"
			       "�������ˡ�\n", me);
		return 1;
	}

	if (! mapp(me->query("private_room")))
	{
		message_vision("³�������Ц����$N�������ݣ��㻹û����"
			       "����ʲô���Ҳ���˵����ӿ��Ƿ����ģ�"
			       "\n", me);
		return 1;
	}

	if (me->query_temp("demolish_room"))
	{
		message_vision("³���$N˵����Ҫ���������ݣ������¾�"
			       "��(demolish)��\n", me);
		return 1;
	}

	message_vision("³���������۾�����ֵĿ���$N���������ò�˵����"
		       "�����浽Ҫ���ݣ����¾��İ�(demolish)��\n", me);
	me->set_temp("demolish_room", 1);
	return 1;
}

// �����ؽ�����Ϣ
private int ask_rebuild()
{
	object me;

	me = this_player();
	if (! mapp(me->query("private_room")))
	{
		message_vision("³��ҡҡͷ����$N˵���㻹û�з����أ�"
			       "̸ʲô�ؽ���\n", me);
		return 1;
	}       
	message_vision("³��̾�˿�������$N˵��������Ҫ�ؽ������Ȱѷ�"
		       "���˰ɣ�\n", me);
	return 1;
}

// ��������Կ��
private int ask_key()
{
	object me;

	me = this_player();

	if (is_busy())
	{
		write("³����æ���أ�û������...\n");
		return 1;
	}

	if (! mapp(me->query("private_room")))
	{
		message_vision("³�࿴��$N���죬��˵��û�з�����ҪԿ"
			       "�׸�ʲô��\n", me);
		return 1;
	}


	if (me->query_temp("ask_for_key"))
	{
		message_vision("³���$Nŭ�������޲���������˵����Կ"
			       "��ʮ�����������������ƽ�\n", me);
		return 1;
	}

	message_vision("³���$N�������ף����Կ��ʮ����������������һ"
		       "���µ�Կ�������ƽ𣬲����ۣ�\n", me);
	me->set_temp("ask_for_key", 1);
	return 1;
}

// ��������������Ϣ
private int ask_desc()
{
	luban_say(@INFORMATION
������Ϣ����ʹ����ɫ�����ҿ��Է��У�������಻�ܳ���160�����֣�

��ɫ�Ĺ���
$BLK$ - ��ɫ	    $NOR$ - �ָ�������ɫ
$RED$ - ��ɫ	    $HIR$ - ����ɫ
$GRN$ - ��ɫ	    $HIG$ - ����ɫ
$YEL$ - ����ɫ	  $HIY$ - ��ɫ
$BLU$ - ����ɫ	  $HIB$ - ��ɫ
$MAG$ - ǳ��ɫ	  $HIM$ - �ۺ�ɫ
$CYN$ - ����ɫ	  $HIC$ - ����ɫ
$WHT$ - ǳ��ɫ	  $HIW$ - ��ɫ

���У�
ֻҪ��������Ϣ�����һ��\n�Ϳ��ԡ����磺"����һ��СԺ��\nԺ�ӱ��ϵ�ǽ�ܰ���"
ʵ�ʿ���������ʹ������ӵģ�
����һ��СԺ��
Ժ�ӱ��ϵ�ǽ�ܰ���

˵����
ϵͳ�Զ����������ַ�����β�˼�һ�� $NOR$ �� \n�����������ò�Ҫ��\n����������
����̫�ࡣ���⣬ϵͳ���Զ��Ĺ淶�������������Ϣ������㲻��Ҫ��������Ϣǰ����
�Ӷ�����ʼ�Ŀո�ͬʱҲ����Ҫ��һ�������ڲ�����\n��ʵ�ֻ��У����ڹ����Ķ���ϵ
ͳ���Զ�����ӻ��з���


INFORMATION );
	return 1;
}

// �����޸ĵ���Ϣ
private int ask_modify()
{
	object me;

	me = this_player();
	if (! submit_form(me->query("id")) &&
	    me->query_temp("contract/luban/questing") != "quest_desc")
	{
		message_vision("³��ҡҡͷ����$N˵����ֻ������ʱ������"
			       "���������Ժ���õ����޸ġ�\n", me);
		return 1;
	}

	message_vision("³����ͷ����$N˵��������޸����ύ�������еĸ�����Ϣ��\n" +
		"\n�����ͨ������ָ���޸ķ��ݵĸ�����Ϣ��\n" +
		HIW "changename " NOR "name : �޸ķ��ݵ��������֡�\n" +
		HIW "changeid   " NOR "id   : �޸ķ��ݵ�Ӣ�Ĵ��š�\n" +
		HIW "changetype " NOR "type : �޸ķ��ݵ����͡�\n" +
		HIW "changedesc " NOR "room desc : �޸�ĳ�䷿�ݵ�������\n", me);
	return 1;
}

// ���³��˵��ʱ�ı���
private void luban_say(string msg)
{
	object me;
	me = this_player();
	message("vision", "³���" + me->query("name") + "���ֹ���˵��"
		"Щ����\n", environment(me), ({ me }));
	tell_object(me, "³��˵����" + msg);
}

// ����û�˵��ʱ�ı���
private void user_say(string msg)
{
	object me;

	me = this_player();
	tell_object(me, "���³��С������" + msg);
	message("vision", me->query("name") + "��³�����ֹ���˵��Щ����"
		"\n", environment(me), ({ me }));
}

// �û���ֹ��̸
private int do_stop()
{
	object me;
	me = this_player();
	if (! me->query_temp("contract/luban"))
	{
		message_vision("³��һ��ɵ��......\n", me);
		return 1;
	}
	me->delete_temp("contract/luban");
	message_vision("³���$N���ͷ��˵������Ȼ��ˣ�������̸Ҳ����"
		       "��\n", me);
	return 1;
}

// �û��ش�����
// ���ݵ�ǰ״̬������Ӧ�ķ�Ӧ
private int do_answer(string arg)
{
	object me;
	string questing;

	me = this_player();
	questing = me->query_temp("contract/luban/questing");

	// �ж������Ƿ�������̸
	if (! questing)
		return 0;

	if (! arg)
		return notify_fail("��ش�ʲô����\n");

	switch (questing) {
	// ��̸��������
	case "quest_name" :
		user_say("���ݵ����־ͽ�" + arg + "�ɣ�\n\n");
		check_name(me, arg);
		break;

	case "quest_id" :
		user_say("���žͽ�" + arg + "�ɣ�\n\n");
		check_id(me, arg);
		break;

	case "quest_type" :
		user_say("�����" + arg + "�ķ�����ô�����Ҿ�Ҫ����ˡ�\n\n");
		check_type(me, arg);
		break;

	default:
		write("û���������⣬����ش�ʲô��\n");
		break;
	}
	return 1;
}

// ��¼�û������������Ϣ
private int do_desc(string arg)
{
	object me;
	string room_name;
	string desc;

	me = this_player();

	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	if (arg)
	{
		if (sscanf(arg, "%s %s", room_name, desc) != 2)
		{
			room_name = arg;
			desc = 0;
		}
	}
	else
	{
		show_desc(me, 0);
		return 1;
	}

	record_desc(me, room_name, desc);
	return 1;
}

// ��ʾ�û��Լ������������Ϣ
private int do_show(string arg)
{
	show_desc(this_player(), arg);
	return 1;
}

// �ı䷿������
// ������״̬������̸�л���������
private int do_changename(string arg)
{
	object me;
	string player_id;
	string position;

	me = this_player();
	player_id = me->query("id");

	if (submit_form(player_id))
	{
		// ��������
		position = query_form(player_id, "position");
		if (! check_legal_name(arg, position)) return 1;

		luban_say("�ðɣ��͸ĳ�" + arg + "������ְɣ�\n");
		set_form(player_id, "name", arg);
		set_form(player_id, "status", "����");
		save();
		return 1;
	} else
	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	// ������̸
	if (check_legal_name(arg, me->query_temp("contract/luban/position")))
	{
		me->set_temp("contract/luban/name", arg);
		luban_say("�ðɣ��͸ĳ�" + arg + "������ְɣ�\n");
	}
	return 1;
}

// �ı䷿�ݴ���
// ������״̬������̸�л���������
private int do_changeid(string arg)
{
	object me;
	string player_id;
	string position;

	me = this_player();
	player_id = me->query("id");

	if (submit_form(player_id))
	{
		// ��������
		position = query_form(player_id, "position");
		if (! check_legal_id(arg, position)) return 1;
		luban_say("�а����͸ĳ�" + arg + "������ݴ��Űɣ�\n");
		set_form(player_id, "id", arg);
		set_form(player_id, "status", "����");
		save();
		return 1;
	} else
	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	// ������̸
	if (check_legal_id(arg, me->query_temp("contract/luban/position")))
	{
		me->set_temp("contract/luban/id", arg);
		luban_say("�а����͸ĳ�" + arg + "������ݴ��Űɣ�\n");
	}
	return 1;
}

// �ı䷿������
// ������״̬������̸�л���������
private int do_changetype(string arg)
{
	object me;
	int value;
	string player_id;
	string position;
	mapping example;

	me = this_player();
	player_id = me->query("id");

	if (! arg)
	{
		user_say("����... �ҿ����ǲ��ǻ������͸���...\n\n");
		check_type(me, arg);
		return 1;
	}

	if (submit_form(player_id))
	{
		// ��������
		user_say("�ҵøĸķ��ͣ��ͻ���" HIC + arg + NOR "�ɡ�\n\n");
		if (! (example = check_legal_type(arg)))
		{
			write("�Ҳ����������͵ķ��ݣ�����û�иı䷿�ݵ����͡�\n");
			return 1;
		}
		set_form(player_id, "room", example["name"]);
		value = example["value"];
		if (wizardp(me)) value = 0;
		set_form(player_id, "value", value);
		set_form(player_id, "descs", ([ ]));
		set_form(player_id, "status", "����");
		save();
		luban_say("��һ�ַ���Ҳ�У�����������д�µ�����(changedesc)��\n");
		return 1;
	} else
	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	// ������̸
	user_say("����... �ҵøĸķ��ͣ��ͻ���" HIC + arg + NOR "�ɡ�\n\n");

	if (! check_type(me, arg))
		write("��û�иı䷿�����͡�\n");
	return 1;
}

// �ı䷿������
// ������״̬������̸�л���������
private int do_changedesc(string arg)
{
	object me;
	string player_id;
	mapping example;
	string room_name;
	string room_desc;

	me = this_player();
	player_id = me->query("id");

	if (submit_form(player_id))
	{
		// ��������
		if (! arg)
			return notify_fail("�밴����ȷ��ʽ���룺changedesc"
					   " room_name description\n");

		if (sscanf(arg, "%s %s", room_name, room_desc) != 2)
		{
			room_name = arg;
			room_desc = 0;
		}

		// �޸�������Ϣ
		modify_desc_in_form(player_id, room_name, room_desc);
		set_form(player_id, "status", "����");
		save();
		return 1;
	} else
	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	// ������̸
	do_desc(arg);
	return 1;
}

// ��������
private int do_finish()
{
	object me;
	int value;
	string msg;

	me = this_player();
	if (me->query_temp("contract/luban/questing") != "quest_desc")
		return 0;

	show_desc(me, 0);

	value = me->query_temp("contract/luban/value");
	user_say("���ˣ���Ū���ˣ�������Ϳ�ʼô��\n\n");
	if (value)
	{
		msg = "���ٲ����������̣�����˹��Ķ�$N˵����Ҫ������"
		      "�ķ��ӣ���˵Ҳ��" + MONEY_D->price_str(value) +
		      "�������ۣ�\n";
		if (wizardp(me))
		{
			msg += "³��Խ��ٺȵ����������������Ͻ�����"
			       "... �ٺ٣���ʱ��˼��˼�����˰ɡ�\n";
		}
	} else
	{
		msg = "�������������̣���$N˵�����������ˣ����������"
		      "��ѣ���ҪǮ��\n";
	}

	msg += "³����һ������Ȼ��˵�����㿴����û��ʲô����ô������û"
	       "�У����Ƚ������ƽ�������ѡ�\n\n";
	message_vision(msg, me);

	return 1;
}

// ������
private int do_withdraw()
{
	object me;

	me = this_player();
	if ( me->query_temp("contract/luban"))
	{
		do_stop();
		return 1;
	}
	if (! query("form/" + me->query("id")))
	{
		message_vision("³��һ��ãȻ......��$N˵�������������"
			       "û���ύ������ɣ�\n", me);
		return 1;
	}

	if (me->query_temp("decide_withdraw"))
	{
		message_vision("³���$N˵����������Ҫ�������룬������"
			       "����(decide)��\n", me);
		return 1;
	}

	switch (query("form/" + me->query("id") + "/status")) {
	case "����":
		luban_say("��ϧ������ô��ͷ����ˣ�\n");
		break;

	case "ͬ��":
		luban_say("��ѽ�����ǿ�ϧ����ʦ��ͬ���ˣ�����ô������"
			  "���ˣ�\n");
		break;

	case "�ܾ�":
		luban_say("����û�ܱ���׼Ҳ��ʹ����ù�ô��������ô��"
			  "����˵ô��\n");
		break;
	}
	message_vision("³��̾�˿�������$N˵������Ȼ��ˣ�����Ҳ������"
		       "ǿ�����������ˣ����¾���(decide)�ɣ�\n", me);
	me->set_temp("decide_withdraw", 1);
	return 1;
}

// ɾ����
private int decide_withdraw()
{
	object me;

	me = this_player();
	if (! me->query_temp("decide_withdraw"))
		return 0;
	
	me->delete_temp("decide_withdraw");
	delete("form/" + me->query("id"));
	save();
	message_vision("³��ҡҡͷ���ͳ�һ���˱������˷�����֪��������"
		       "ʲô������\n", me);
	return 1;
}

// ��ٷ���
// ������ѯ��³���йز𷿵���Ϣ
private int do_demolish()
{
	object me;

	me = this_player();
	if (! me->query_temp("demolish_room"))
		return notify_fail("��Ҫ��ʲô�����ݿ�Ҫ�Ⱥ�³��˵һ����\n");

	me->delete_temp("demolish_room");
	demolish_room(me);
	return 1;
}

// ��ٷ��ݵ�ִ�к������ú������ܻᱻ�ⲿ���ã����Ա���쿴Ȩ��
int demolish_room(object me)
{
	string *names;
	string room_name;
	string key_id;
	string this_key_id;
	mixed *file;
	string fdir;

	object ob;
	object *obs;

	int i;

	if (! is_root(previous_object()))
	{
		write ("��û��Ȩ����ٷ��ݡ�\n");
		return 0;
	}
	    
	if (! mapp(me->query("private_room")))
	{
		write("���ݴ����޷�����ִ�У�\n");
		return 0;
	}

	// ��������е�Կ�ף��������ڵ�ǰ������г����⡣
	room_name = me->query("private_room/name") + "(" +
		    me->query("private_room/id") + ")";
	command("chat ������" + me->query("name") + "��" +
		room_name + "Կ�׵ģ������Կ�׽��ص�����������");

	key_id = "1 of " + me->query("id");
	obs = users();
	for (i = 0; i < sizeof(obs); i++)
	{
		int flag;
		int k;
		object *carries;

		if ((i + 1) % 100 == 0)
			// ��ִֹ��ʱ���������������
			reset_eval_cost();

		// ȥ������������б��ٵ���ס����Կ��
		carries = all_inventory(obs[i]);
		for (k = 0, flag = 0; k < sizeof(carries); k++)
		{
			if (! carries[k]->id("key"))
				continue;

			if (sscanf(carries[k]->query("id"), "%*d of %s", this_key_id) != 2 ||
			    this_key_id != key_id)
				continue;

			destruct(carries[k]);
			if (flag) continue;

			tell_object(obs[i], "\n��������Ϻ������˵�ʲô"
					    "��������ϸһ��ԭ����" +
					    me->query("name") +
					    "�ҵ�Կ�ײ����ˡ�\n\n");
			flag = 1;
		}
	}

	// ��ִֹ��ʱ���������������
	reset_eval_cost();

	// ɾ���û������������ļ�
	// ͬʱɾ��Կ���ļ���Կ���п�������ĳЩ���������Ե�¼��
	// ʱ����ܻ����һЩ���⡣
	fdir = file_dir(me);
	file = get_dir(fdir, -1);
	seteuid(getuid());
	if (file)
	{
		// ��������еĶ���(object)
		for (i = 0; i < sizeof(file); i++)
		{
			object room;

			if (strsrch(file[i][0], ".c") == -1)
				continue;

			room = find_object(fdir + file[i][0]);
			if (room)
			{
				message("vision", "ͻȻ����ͯ�ӷ�Ҳ��"
					"�ĳ��˹�����������Ÿ��ּһ�"
					"�����µ�����������������\n",
					room);
				catch(DBASE_D->clear_object(room));
			} else
			{
				// clear the data in dbase
				catch(DBASE_D->clear_object(fdir + file[i][0][0..<3]));
			}
		}

		// Ȼ������ļ�����Ϊ��������ʱ���п�����Ϊ����
		// ���ȶ������ļ�
		file = get_dir(fdir, -1);
		for (i = 0; i < sizeof(file); i++)
			rm(fdir + file[i][0]);
	}
	rmdir(fdir);

	ob = get_object(me->query("private_room/position"));
	if (! objectp(ob))
	{
		write("�йط��ݵ���Ϣ�Ѿ���ɾ�������ǽ����ĵص��Ѿ���"
		      "�����ˣ������ʦ��ϵ�ɡ�\n");
		me->delete("private_room");
		me->save();
		return 0;
	}

	ob->destroy_room(me->query("private_room/id"));
	ob->save();
	me->delete("private_room");
	me->save();
	if (environment(me) == environment(this_object()))
	{
		// ������ֳ�
		message_vision("³����ͷ����$N˵�����ˣ�ʣ�µ�����"
			       "�һ���׵ģ���������ˡ�\n", me);
	}

	return 1;
}

// ��ʾ�û������������Ϣ
// ����û�������̸������ʾ�û��������������Ϣ������û��ڵȴ�����������ʾ�û�
// ��ǰ�����������Ϣ
// ���һ��player�Է��ݵ�����
// room_name���û�ָ���ķ����е�ĳһ���short����
private void show_desc(mixed player, string room_name)
{
	mapping filesp;	 // ԭ�ͷ����������ļ�mapping
	mapping descsp;	 // ��ҵ�����mapping

	int i;
	int value;	      // �������
	int count;	      // ��ʾ��������Ϣ����Ŀ
	object me;	      // ���øú����Ķ���
	object ob;	      // �������ķ��ݵ�object���ǽ���������object

	string player_id;       // ���췿�ݵ����ID
	string desc;	    // ����������mapping
	string *names;	  // ����mapping�Ĺؼ��ֵ��ַ�����
	string room_nameid;     // �������ּ�ID
	string room_type;       // ��������
	string position;	// ������λ��

	string ids;	     // ��ѯʱʹ��

	string info;	    // ����������ʾ��Ϣ
	string msg;	     // ��ʱ������������ʾ��Ϣ

	me = this_player();
	info = "";

	if (objectp(player))
		player_id = player->query("id");
	else
	if (stringp(player))
		player_id = player;
	else
		return;

	if (mapp(query("form/" + player_id)))
	{
		// �ڱ����и�����ύ�ı�
		ids = "form/" + player_id + "/";
		room_type = query(ids + "type");
		for (i = 0; i < sizeof(room_example); i++)
		{
			if (room_example[i]["type"] == room_type)
			{
				filesp = room_example[i]["files"];
				break;
			}
		}
		if (! mapp(filesp))
		{
			write("������ķ�������(" + room_type + ")�Ѿ�"
			      "�������ˣ������ʦ��ϵ��\n");
			return;
		}
		descsp = query(ids + "descs");
		room_type = query(ids + "room") + "(" + room_type + ")";
		room_nameid = query(ids + "name") + "(" + query(ids + "id") + ")";
		value = query(ids + "value");
		position = query(ids + "position");
		// ��ʾ��Ϣ�и����÷��ݵ�������
		msg = query(ids + "wizard");
		switch (query(ids + "status")) {
		case "����" :
			info = "��ʦ��û�в���������롣";
			break;

		case "�ܾ�" :
			info = msg + "�Ѿ��ܾ���������룡";
			if (query(ids + "memo") != "��")
				info += "\nԭ���ǣ�" + query(ids + "memo");
			break;

		case "ͬ��" :
			info = msg + "�Ѿ�ͬ����������룡";
			break;
		}

		if (this_player()->query("id") == player_id)
		{
			if (query(ids + "status") == "ͬ��")
			{
				info += HIW "\n�����ڿ��Խ��췿���ˡ�"
					"�����ʱ�޸��˷��ݵ���Ϣ����"
					"Ҫ�õ���ʦ���ٴ���׼��" NOR;
			} else
			if (query(ids + "status") == "�ܾ�")
			{
				info += HIR "\n����������޸ķ��ݵ���"
					"Ϣ�Ի����ʦ����׼�������볷"
					"�����롣" NOR;
			}
			info += "\n����Գ���(withdraw)���ύ�����롣";
		}
	} else
	if (objectp(player = present(player_id, environment(this_object()))) &&
	    player->query_temp("contract/luban/questing") == "quest_desc")
	{
		// �ҵ�����³����ǰ������̸�����
		filesp = player->query_temp("contract/luban/room/files");
		descsp = player->query_temp("contract/luban/descs");
		room_type = player->query_temp("contract/luban/room/name");
		room_type += "(" + player->query_temp("contract/luban/room/type") + ")";
		room_nameid = player->query_temp("contract/luban/name") + "(" +
			      player->query_temp("contract/luban/id") + ")";
		value = player->query_temp("contract/luban/value");
		position = player->query_temp("contract/luban/position");
	} else
	{
		// û����̸
		luban_say("�Ǻǣ���λ����û�д��㽨���Ӱɡ�\n");
		return;
	}

	ob = get_object(position);
	if (! objectp(ob))
	{
		write("������Ľ��췿�ݵĵط�(" + position + ")�Ѿ���"
		      "�����ˣ������ʦ��ϵ!\n");
		return;
	}

	user_say("���������ҿ���" + room_nameid + "����������ô����\n\n");
	msg = "�ã��㿴���ɣ�" + "����ѡ�õ���" + room_type +
	      "�������͵ķ��ݡ�\n����������" + room_nameid +
	      "����������" + ob->query("short");
	if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
		msg += "(" + position + ")";
	msg += "��\n";
	luban_say(msg);

	names = keys(filesp);
	count = 0;
	for (i = 0; i < sizeof(filesp); i++)
	{
		// ���Ҹ÷��ݵ�object
		ob = get_object(filesp[names[i]]);
		if (! objectp(ob))
		{
			write(HIR "�Ҳ���ʾ���ķ���(" + names[i] + "::" + filesp[names[i]] + ")�������ʦ��ϵ��"NOR"\n");
			continue;
		}
		if (! room_name || room_name == "" ||
		    ob->query("short") == room_name || names[i] == room_name)
		{
			// �����û������������Ϣ
			desc = descsp[names[i]];
			write(YEL "������������������������������������������������������������������������������"NOR"\n");
			write(YEL + "����" + ob->query("short") + "(" + names[i] + ")" + YEL + "��������\n" + NOR);
			if (! desc)
			{
				// �û�û������������Ϣ����ʾȱʡ��Ϣ
				desc = CYN "���ڻ�û������������Ϣ��ʹ"
				       "��ȱʡ��������Ϣ�����£�\n";
				desc += "    ";
				if (stringp(ob->query("default_long")))
					desc += sort_desc(player,
							  ob->query("default_long"));
				else
					desc += sort_desc(player,
							  replace_string(ob->query("long"), "\n", ""));
				desc += NOR;
			} else
				desc = "    " + sort_desc(player, desc);
			write(desc);
			count++;
		}
	}

	if (! count)
	{
		write("��������û��" + room_name + "������䣬����show�鿴���еķ��䣡\n");
		return ;
	}

	write(YEL "������������������������������������������������������������������������������"NOR"\n");
	write("�������������г�����Щ���ݡ�\n");

	if (! value)
		info += "\n������Щ���䲻��Ҫ�����κ�������";
	else
		info += "\n������Щ������Ҫ����" HIY + MONEY_D->price_str(value) + NOR "��";

	write(info + "\n\n");

	return ;
}

private void promote_type(object me)
{
	int i;
	int len;
	string msg;

	msg = "���۹�����һɨ�������ķ��������У�" +
	      room_example[0]["name"] + "(" +
	      room_example[0]["type"] + ")";
	len = strlen(msg);
	for (i = 1; i < sizeof(room_example); i++)
	{
		string temp;

		temp = "��" + room_example[i]["name"] + "(" +
			      room_example[i]["type"] + ")";
		msg += temp;
		len += strlen(temp);
		if (len > 70)
		{
			msg += "\n";
			len = 0;
		}
	}
	if (len) msg += "��\n";
	tell_object(me, msg);
}

// ѯ����ұ�Ҫ�Ľ�����Ϣ��Ȼ���¼��������ʦ����
private int quest_user(object me)
{
	message_vision("³���$N˵�����ã�����������ϸ̸̸��\n", me);
	// ѯ�ʷ�������
	luban_say("�ȸ��������뽨�ķ��ӽ�ʲô����(answer name)��\n"
		  "�����ǲ���̸��(stop)��������Ҳ�޷���\n");
	me->set_temp("contract/luban/questing", "quest_name");
	return 1;
}

// ѯ��������Ϣ
private int quest_info(object me)
{
	message_vision("³���$N˵�����ã�������ϲ��" +
		       me->query_temp("contract/luban/room/name") +
		       "������ʽ�ġ�\n", me);
	// ��ʾ������ʽ��Ϣ
	
	luban_say(@INFORMATION
�����Ϊ��ķ��������ϲ������������ʽ�ǣ�desc �������� ��������
Ȼ��Ҳ����ʹ��ԭ�е�������������뿴��������������������show���쿴��
��һ�ж���������Ժ����finish����ok�Ϳ����ˡ�������޸�����ķ�����
�֣����ţ����͵���Ϣ��������ѯ��<�޸�>�ķ�����

�ٸ����������ӣ�"desc СԺ ������һ����µ�СԺ��"�����͸�СԺ���
��һ�������������ȡ��СԺ���������Լ��룺"desc СԺ"�Ϳ����ˡ�

����������ʹ����ɫ�����Զ��У�����ϸ�ڿ������� <����> ����Ҫ��Ҫע��
���ǣ�ϵͳ�Զ����������ַ�����β�˼�һ�� $NOR$ �� \n�����������Ҫ��
\n�������������̫�࣬��֮���š����⣬ϵͳ���Զ��Ĺ淶�������������
Ϣ������㲻��Ҫ��������Ϣǰ����Ӷ�����ʼ�Ŀո�ͬʱҲ����Ҫ��һ��
�����ڲ�����\n��ʵ�ֻ��У����ڹ����Ķ���ϵͳ���Զ�����ӻ��з���

���⣬���������ַ����ڲ���Ҫ����ո�������Щ���붼�ᱻĨ����
INFORMATION );

	me->set_temp("contract/luban/questing","quest_desc");

	// ���������Ϣ
	me->delete_temp("contract/luban/descs");
	me->set_temp("contract/luban/descs", ([ ]));
	return 1;
}

// �ж��û�����ķ�������
private int check_name(object me, string arg)
{
	if (! arg)
	{
		luban_say("����ô��˵����Ҫ�ǲ���̸��(stop)����˵���ǣ�\n");
		return 0;
	}

	if (! check_legal_name(arg, me->query_temp("contract/luban/position")))
		return 0;

	// ��¼��̸�õķ�������
	me->set_temp("contract/luban/name", arg);

	luban_say("��ȷ����ķ��ݵĴ���(3��10��Ӣ����ĸ)�����Ǻ��˾ͻ�"
		  "����(answer id)��\n");
	me->set_temp("contract/luban/questing", "quest_id");
	return 1;
}

// �ж��û�����ķ��ݴ���
private int check_id(object me, string arg)
{
	if (! arg)
	{
		luban_say("����ô��˵����Ҫ�ǲ���̸��(stop)����˵���ǣ�\n");
		return 0;
	}

	if (! check_legal_id(arg, me->query_temp("contract/luban/position")))
		return 0;

	// ��¼��̸�õķ��ݴ���
	me->set_temp("contract/luban/id", arg);

	luban_say("����Ҫ������ʽ��ס��(answer type)? ���ǲ�̫�������"
		  "���Ե�������СԺһ�ۡ�\n");
	promote_type(me);
	me->set_temp("contract/luban/questing","quest_type");   
	return 1;
}

// �ж��û�����ķ�������
private int check_type(object me, string arg)
{
	mapping *example;
	int value;

	if (! arg)
	{
		luban_say("����Ҫ������ʽ��ס��(answer type)�����ǲ�"
			  "̫���������Ե�������СԺһ�ۡ�\n");
		promote_type(me);
		return 0;
	}

	if (! (example = check_legal_type(arg)))
	{
		luban_say("��Ҫ����ʽ��ϡ�棬�������ڻ�û�С��������"
			  "�ٸ����ҡ�\n");
		return 0;
	}
	// ��¼�û�ѡ���ķ�������
	me->set_temp("contract/luban/room", example);

	// ���㷿�ݵļ�ֵ
	value = me->query_temp("contract/luban/room/value");
	if (wizardp(me)) value = 0;
	me->set_temp("contract/luban/value", value);

	quest_info(me);
	return 1;
}

// �ж��û�����ķ������Ƿ�Ϸ�
// ͬʱ�жϸô��Ƿ��Ѿ���ס��
private int check_legal_name(string name, string position)
{
	object ob;

	if ((strlen(name) < 4) || (strlen(name) > 12 )) {
		write("�Բ����㷿�ݵ����ֱ����� 2 �� 6 �������֡�\n");
		return 0;
	}

	if (!is_chinese(name))
	{
		write("�Բ��������á����ġ�Ϊ����ȡ���֡�\n");
		return 0;
	}

	ob = get_object(position);
	if (! objectp(ob)) return 1;

	if (ob->query_room_name(name))
	{
		luban_say("�Բ��𣬾�����֪�������Ѿ���һ��ס�������"
			  "�����ˣ���������һ�����֡�\n");
		return 0;
	}

	return 1;
}

// �ж��û�����ķ��ݴ����Ƿ�Ϸ�
private int check_legal_id(string roomid, string position)
{
	object ob;
	int i;

	i = strlen(roomid);
	
	if( (strlen(roomid) < 3) || (strlen(roomid) > 10 ) ) {
		write("�Բ����㷿�ݵĴ��ű����� 3 �� 10 ��Ӣ����ĸ��\n");
		return 0;
	}
	while(i--)
	{
		if(((roomid[i] < 'A') || (roomid[i] > 'Z')) &&
		   ((roomid[i] < 'a') || (roomid[i] > 'z')))
		{
			write("�Բ����㷿�ݵĴ��ű�����Ӣ����ĸ��\n");
			return 0;
		}
	}

	if (member_array(roomid, ban_room_id) != -1)
	{
		command("shake");
		luban_say("��Ҫ���������֣�����˼���ᡣ\n");
		return 0;
	}

	ob = get_object(position);
	if (! objectp(ob)) return 1;

	if (ob->query_room_id(roomid))
	{
		luban_say("�Բ��𣬾�����֪�������Ѿ���һ��ס��ʹ����"
			  "���Ӣ�Ĵ����ˣ�����ѡһ����\n");
		return 0;
	}

	return 1;
}

// �ж��û�����ķ��������Ƿ����
// ��������򷵻��Ǹ��������Ͷ�Ӧ��mapping��ָ��
private mixed check_legal_type(string type)
{
	int i;
	for (i = 0; i < sizeof(room_example); i++)
	{
		if (room_example[i]["type"] == type ||
		    room_example[i]["name"] == type )
		return room_example[i];
	}
	return;
}

// ���һ�����ݶ���
private object get_object(string file_name)
{
	object ob;

	if (! file_name || file_name == "")
		return 0;

	if (! (ob = find_object(file_name)))
		ob = load_object(file_name);

	return ob;
}

// ��¼�û�����ĳһ�䷿�����Ϣ
private int record_desc(object me, string room_name, string desc)
{
	mapping filesp;
	mapping descsp;

	int i;
	object ob;
	string *names;

	if (! (desc = obey_description(desc))) return 0;

	filesp = me->query_temp("contract/luban/room/files");
	descsp = me->query_temp("contract/luban/descs");

	names = keys(filesp);
	for (i = 0; i < sizeof(names); i++)
	{
		// ���Ҹ÷��ݵ�object
		ob = get_object(filesp[names[i]]);
		if (ob->query("short") == room_name || names[i] == room_name)
		{
			// �����û������������Ϣ
			if (! desc || desc =="")
			{
				string msg;
				msg = "��û����������" + ob->query("short") + "(" +
				      room_name + ")����Ϣ����ʹ��ϵͳȱʡ��������Ϣ��\n";
				msg += CYN "ȱʡ��������Ϣ���£�\n";
				if (stringp(ob->query("default_long")))
				      msg += sort_desc(me, ob->query("default_long"));
				else
				      msg += sort_desc(me, replace_string(ob->query("long"), "\n", ""));
				msg += NOR;
				write(msg);
				map_delete(descsp, names[i]);
			} else
			{
				descsp[names[i]] = desc;
				write("��������" + ob->query("short") +
				      "(" + room_name + ")��\n");
			}
			return 1;
		}
	}
	write("û���ҵ�" + room_name + "�����֤������������Ϣ��\n");
	return 0;
}

// �����û�����Ľ�����Ϣ
private void record_contract(object me)
{
	string id;
	mapping descp;

	id = me->query("id");
	if (! mapp(query("form"))) delete("form");

	set_form(id, "player", me->query("name"));
	set_form(id, "name", me->query_temp("contract/luban/name"));
	set_form(id, "id", me->query_temp("contract/luban/id"));
	set_form(id, "room", me->query_temp("contract/luban/room/name"));
	set_form(id, "type", me->query_temp("contract/luban/room/type"));
	set_form(id, "position", me->query_temp("contract/luban/position"));
	set_form(id, "value", me->query_temp("contract/luban/value"));
	set_form(id, "time", time());
	set_form(id, "status", "����");
	set_form(id, "wizard", "��");
	set_form(id, "memo", "��");

	descp = me->query_temp("contract/luban/descs");

	set_form(id, "descs", descp);
	save();
}

// �ı��������ĳһ�䷿�����Ϣ
// �޸ĵ������Ǵ����form�е�
private int modify_desc_in_form(string player_id, string room_name, string desc)
{
	mapping example;
	mapping filesp;
	mapping descsp;

	int i;
	object ob;
	string *names;

	if (! (desc = obey_description(desc))) return 0;

	if (! (example = check_legal_type(query_form(player_id, "type"))))
	{
		write("���ַ��ݵ������Ѿ��������ˣ�����û�иı䷿�ݵ������������ʦ��ϵ��\n");
		return 1;
	}

	filesp = example["files"];
	descsp = query_form(player_id, "descs");
	names = keys(filesp);

	for (i = 0; i < sizeof(names); i++)
	{
		// ���Ҹ÷��ݵ�object
		ob = get_object(filesp[names[i]]);
		if (ob->query("short") == room_name || names[i] == room_name)
		{
			// �����û������������Ϣ
			if (! desc || desc =="")
			{
				write("��û����������" + room_name +
				      "����Ϣ����ʹ��ϵͳȱʡ��������Ϣ��\n");
				write("ȱʡ��������Ϣ���£�\n" +
				      stringp(ob->query("default_long")) ?
				      sort_desc(player_id, ob->query("default_long")) :
				      sort_desc(player_id, replace_string(ob->query("long"), "\n", "")));
				map_delete(descsp, names[i]);
			} else
			{
				descsp[names[i]] = desc;
				write("������������" + ob->query("short") + "��\n");
			}
			return 1;
		}	       
	}
	write("û���ҵ�" + room_name + "������û���޸�������Ϣ�����֤���޸�������Ϣ��\n");
	return 0;
}

// ��һ���������ַ������滯
private string obey_description(string desc)
{
	if (strlen(desc) > 420)
	{
		luban_say("�������Ҳ̫���˰�...\n");
		return 0;
	}

	if (! desc || desc == "") return "";

	desc = replace_string(desc, "\"", "'");
	desc = replace_string(desc, "\\", "\\\\");
	desc = replace_string(desc, "\\n", "\n");
	desc = replace_string(desc, "\t", "");

	desc = replace_string(desc, "$BLK$", BLK);
	desc = replace_string(desc, "$RED$", RED);
	desc = replace_string(desc, "$GRN$", GRN);
	desc = replace_string(desc, "$YEL$", YEL);
	desc = replace_string(desc, "$BLU$", BLU);
	desc = replace_string(desc, "$MAG$", MAG);
	desc = replace_string(desc, "$CYN$", CYN);
	desc = replace_string(desc, "$WHT$", WHT);
	desc = replace_string(desc, "$HIR$", HIR);
	desc = replace_string(desc, "$HIG$", HIG);
	desc = replace_string(desc, "$HIY$", HIY);
	desc = replace_string(desc, "$HIB$", HIB);
	desc = replace_string(desc, "$HIM$", HIM);
	desc = replace_string(desc, "$HIC$", HIC);
	desc = replace_string(desc, "$HIW$", HIW);
	desc = replace_string(desc, "$NOR$", NOR);

	desc = desc + NOR;

	return desc;
}

// ���������������
private int do_help(string arg)
{
	if (! arg)
		return notify_fail("��Ҫ��ѯʲô������Ϣ��\n");

	switch (arg)
	{
	case "list":
		write(@WRITE
�г����л����ǲ�������ύ�ı������������all ����û�У���
�����еı��г������������apply�� ���г����������еı���
���������agree�� ���г������Ѿ���׼�ı������������reject
���г������Ѿ�����ʦ�ܾ��ı�������old �������г���û��ִ��
�ı��г�����

�������list all | apply | agree | reject | old
WRITE );
		return 1;

	case "type":
		write(@WRITE
��ʾĳ������ύ���еľ���������Ϣ�����ָ���˷������ƣ���
ֻ��ʾ����Ҷ��ڸ÷��ݵ�������

�������type ���ID [��������]
WRITE );
		return 1;

	case "agree":
		write(@WRITE
��׼ĳ������ύ�ı�����׼�Ժ����ֻ��Ҫ�����ֽ𼴿ɽ�����

�������agree ���ID
WRITE );
		return 1;

	case "reject":
		write(@WRITE
�ܾ�ĳ������ύ�ı��������ھܾ���ʱ��˵��ԭ��ԭ�򽫼�¼
�ڱ��еı�ע�С�

�������reject ���ID [ԭ��]
WRITE );
		return 1;

	case "delete":
		write(@WRITE
ɾ��ĳ������ύ�ı������������״̬���ܱ�ɾ��������ܾ�
��ͬ���Ժ�ſ���ɾ��������Ϊ�˱�����ҳ���û�д����Լ��ύ��
�������õ����

�������delete ���ID
WRITE );
		return 1;
	}
}

// �г���
// ��ʦʹ��
private int do_list(string arg)
{
	if (! exist_form()) return 1;

	if (! arg || arg == "all" || arg == "ȫ��" || arg == "����")
	{
		show_all();
		return 1;
	}

	switch (arg) {
	case "apply":
	case "����":
	case "new":
		show_apply();
		return 1;

	case "agree":
	case "ͬ��":
	case "��׼":
		show_agree();
		return 1;

	case "reject":
	case "���":
	case "����׼":
	case "û��׼":
		show_reject();
		return 1;

	case "old":
	case "��":
		show_old();
		return 1;
	}

	write("list��ʹ��˵����\nlist all   : ��ʾ���еı���\nlist apply : ��ʾ����ı���\n" +
	      "list agree : ��ʾ��ʦ�Ѿ���׼�ı���\nlist reject : ��ʾ��ʦ�Ѿ�����ı���\n" +
	      "list old   : ��ʾ���ںܾõı���\n\n");
	return 1;
}

// ��ʾ������ϸ��Ϣ
// ��ʽ��type player_id room_name ��ʾ��player������ĳ�䷿��
//   ��type player_id	   ��ʾ��player����������
// ��ʱ�������������������룬Ҳ���Բ쿴
private int do_type(string arg)
{
	string player_id;
	string room_name;
	int a;

	if (! wizardp(this_player()) || wiz_level(this_player()) < WIZLEVEL)
	{
		write("����Ȩ�쿴���е�������Ϣ��\n");
		return 1;
	}
	if (! arg)
	{
		write("usage: type player_id [room_name]\n");
		return 1;
	}

	if (sscanf(arg, "%s %s", player_id, room_name) != 2)
	{
		player_id = arg;
		room_name = "";
	}

	show_desc(player_id, room_name);
	return 1;
}

// ��ʾһ������ļ�Ҫ˵��
private void show_brief(string player_id)
{
	mapping form;
	string msg;
	string wizard;
	string memo;
	int i;

	form = query("form/" + player_id);
	if (! form || ! mapp(form)) return;

	// �����ߵĴ��� ����������  ����ʱ��    ��  ��  ״̬  �� �� ��  ��   ע
	// 12	   .10	. 10	. 6      .4    .8	 .16
	msg = sprintf("%-12s  %-10s  %-10s  %-6s",
		      player_id, form["player"],
		      ctime(form["time"])[0..9], form["room"]);

	// ��ʵ����״̬
	switch (form["status"]) {
	case "����" :
		msg += HIW;
		break;

	case "ͬ��" :
		msg += HIY;
		break;

	case "�ܾ�" :
		msg += HIR;
		break;
	}
	msg += "  " + form["status"] + NOR + "  ";

	wizard = form["wizard"];
	memo = form["memo"];

	if (! stringp(wizard) || wizard == "��" || wizard == "")
		wizard = "--------";

	if (! stringp(memo) || memo == "��" || memo == "")
		memo = "------";

	msg += sprintf("%-8s  %s\n", wizard, memo);
	write(msg);
	return;
}

// �жϱ��Ƿ���ڣ��������Ƿ����ʸ���ñ�
private int exist_form()
{
	if (! mapp(query("form")) || sizeof(query("form")) < 1)
	{
		write("����³�����ﲢû���κα���Ҫ����\n");
		return 0;
	}
	if (! wizardp(this_player()) || wiz_level(this_player()) < WIZLEVEL)
	{
		write("����Ȩ�������\n");
		return 0;
	}
	return 1;
}

// ��׼��
// ��ʦʹ��
private int do_agree(string arg)
{
	object ob;
	if (! exist_form()) return 1;

	if (! arg || ! query("form/" + arg))
	{
		write("usage: agree playerid\n");
		return 1;
	}
	
	if (query("form/" + arg + "/status") == "ͬ��")
	{
		write("�˱��Ѿ�����׼�ˡ�\n");
		return 1;
	}
	set("form/" + arg + "/status", "ͬ��");
	set("form/" + arg + "/wizard", this_player()->query("name"));
	set("form/" + arg + "/memo", "��");
	write("����׼��" + query("form/" + arg + "/player") + "(" + arg + ")�����롣\n");
	save();

	if (objectp(ob = find_player(arg)) && ob != this_player())
		tell_object(ob, HIG + name() + "�����㣺��ı��Ѿ���" +
			    this_player()->name() + "��׼�ˣ�������Ǯ�ɡ�\n" + NOR);

	return 1;
}

// �ܾ���
// ��ʦʹ��
private int do_reject(string arg)
{
	object ob;
	string player;
	string memo;

	if (! exist_form()) return 1;

	if (! arg)
	{
		write("usage: reject player_id [because]\n");
		return 1;
	}

	if (sscanf(arg, "%s %s", player, memo) != 2)
	{
		player = arg;
		memo = "��";
	}

	if (! query("form/" + player))
		return notify_fail("��Ҫ����˭�ı���\n");

	if (memo == "��")
	{
		write("�������ӱ�ע��Ϣ(reject player ��ע��Ϣ)��˵���ܾ������ɡ�\n");
	}

	set("form/" + player + "/status", "�ܾ�");
	set("form/" + player + "/wizard", this_player()->query("name"));
	set("form/" + player + "/memo", memo);

	write("���Ѿ��ܾ���" + query("form/" + player + "/player") + "(" + player + ")�����롣\n");
	save();

	if (objectp(ob = find_player(arg)) && ob != this_player())
		tell_object(ob, HIG + name() + "�����㣺��ı��Ѿ���" +
			    this_player()->name() + HIR "�ܾ�" NOR HIG
			    "�ˣ����������ɡ�\n" + NOR);
	return 1;
}

// ɾ����
// ��ʦʹ��
private int do_delete(string arg)
{
	if (! exist_form()) return 1;

	if (! arg)
	{
		write("usage: delete player_id\n");
		return 1;
	}

	if (query("form/" + arg + "/status") == "����")
	{
		return notify_fail("�㲻��ɾ��һ�������û�д���ı���\n");
	}

	write((string)query("form/" + arg + "/player") + "(" + arg +
	      ")�ύ�ı���ɾ���ˡ�\n");
	delete("form/" + arg);
	save();

	return 1;
}

// ��ʾ�ո�����ı�
private void show_apply()
{
	show_brief_list("����", HIW + "����������ύ������ı�" + NOR);
}

// ��ʾ����׼�ı�
private void show_agree()
{
	show_brief_list("ͬ��", HIY + "��������ʦ�Ѿ���׼����ı�" + NOR);
}

// ��ʾ���ܾ��ı�
private void show_reject()
{
	show_brief_list("�ܾ�", HIR + "�����Ǳ���ʦ�ܾ�����ı�" + NOR);
}

// ��ʾ���ܾ��ı�
private void show_all()
{
	show_brief_list(0, HIG + "���������еı�" + NOR);
}

// ��ʾ�Ƚϳ¾ɵı� - ����15��ı�
private void show_old()
{
	int i;
	int count;

	string *ids;

	if (! exist_form()) return;

	count = 0;
	ids = keys(query("form"));
	for (i = 0; i < sizeof(ids); i++)
	{
		if (query("form/" + ids[i] + "/time") - time() > 86400 * 15)
		{
			// ����15��ı�
			if (! count)
			{
				write(HIC "����������ύ�˺ܾõı���\n" + NOR);
				write(YEL "��������������������������������������������������������������������������������"NOR"\n");
				show_brief_title();
			}
			count++;
			show_brief(ids[i]);
		}
	}
	if (count)
	{
		write(YEL "��������������������������������������������������������������������������������"NOR"\n");
		write("����" + ((string) count) + "�űȽϳ¾ɵı���\n");
	} else
		write("Ŀǰû�г¾ɵı���\n");
}

// ��ʾ�б�
// info����ʾ�ı������� - infoΪ�ձ�ʾ��ʾ���б�
// msg����ʾ���б������ - ��"������ʦ��׼�ı�"
private void show_brief_list(string info, string msg)
{
	int i;
	int count;

	string *ids;

	if (! exist_form()) return;

	count = 0;
	ids = keys(query("form"));
	for (i = 0; i < sizeof(ids); i++)
	{
		if (! info || query("form/" + ids[i] + "/status") == info)
		{
			if (! count)
			{
				write(msg + "\n");
				write(YEL "��������������������������������������������������������������������������������"NOR"\n");
				show_brief_title();
			}
			count++;
			show_brief(ids[i]);
		}
	}
	if (count)
	{
		write(YEL "��������������������������������������������������������������������������������"NOR"\n");
		write("����" + ((string) count) + "�ű���\n");
	} else
		write("Ŀǰû���κη���Ҫ��ı���\n");
}

// ��ʾ�б���ͷ
private void show_brief_title()
{
	write(WHT "�����ߵĴ���  ����������  �����ʱ��  ��  ��  ״̬  ������ʦ  ��   ע"NOR"\n");
}

// ����һ�������췿��
private void create_room(object me)
{
	mapping filesp;	 // �����ԭ�ͷ����ļ�mapping
	mapping descsp;	 // �����д������mapping

	string player_id;       // ���ҷ������ҵ�ID
	string room_type;       // ��������
	string room_name;       // ��������
	string room_id;	 // ����ID
	string room_key;	// ���ݵ�Կ��
	string room_owner;      // ���ݵ�����
	string position;	// ���췿�ݵĵص�(·����)
	string position_short;  // ���췿�ݵĵص����������
	string outdoors;	// �������ڵ�����
	string entry;	   // ���ݵ����

	string *content;	// Դ�ļ�������
	string *names;	  // filesp�Ĺؼ��ּ���
	string filename;	// ���ɵ��ļ�����
	string dstfile;	 // ���ɵ��ļ�����

	string desc;	    // ĳ�䷿�ݵ�����::Կ�׵�����
	object ob;	      // ���ݵ�object

	int i;
	int k;
	string ids;	     // ��ݲ�ѯ�ַ���

	me = this_player();
	if (! objectp(me)) return;

	player_id = me->query("id");
	room_name = me->query("name");
	entry = "";

	if (! mapp(query("form/" + player_id)))
	{
		// û���ҵ�����ύ�ı�
		return;
	}

	// �ڱ����и�����ύ�ı�
	ids = "form/" + player_id + "/";
	room_type = query(ids + "type");
	for (i = 0; i < sizeof(room_example); i++)
	{
		if (room_example[i]["type"] == room_type)
		{
			filesp = room_example[i]["files"];
			break;
		}
	}

	if (! mapp(filesp))
	{
		write("������ķ�������(" + room_type + ")�Ѿ���������"
		      "�������ʦ��ϵ��\n");
		return;
	}

	descsp = query(ids + "descs");
	room_type = query(ids + "room");
	room_name = query(ids + "name");
	room_id = query(ids + "id");
	room_owner = query(ids + "player");
	position = query(ids + "position");
	names = keys(filesp);

	room_key = "1 of " + player_id;

	ob = get_object(position);
	if (! objectp(ob))
	{
		write ("�㽨���ĵص��Ѿ��������ˣ������ʦ��ϵ��\n");
		return ;
	}
	position_short = ob->query("short");
	if (! (outdoors = ob->query("outdoors")))
		outdoors = "unknow";
	message("vision", HIY "³�������֣�˵���������ǣ��������ˣ�׬����"
			      "���ӵ�ʱ���ˣ�����"NOR"\n" +
			  YEL "��ʱ���ذ�����ֻ������ǰģģ������ʲôҲ"
			      "�����������Ȼ��֪��������ʲô���顣"NOR"\n",
			  environment());

	// ���벢�������е��ļ�
	for (i = 0; i < sizeof(names); i++)
	{
		// long_flag ��Ϊ�˽�ԭ�ͷ��ļ��г�����@LONG��LONG֮����ַ���ȥ����ʹ�õı�־��
		int long_flag;

		// enter_receive ��Ϊ����������Ŀ���ʹ�õ�
		int enter_receive;

		if (file_size(filesp[names[i]]) <= 0)
		{
			write("ȱ���ļ�:" + filesp[names[i]] +
			      "���������ɷ��ݣ������ʦ��ϵ��\n");
			// ɾ���Ѿ��������ļ�
			for (k = i - 1; k >= 0; k--)
				rm(to_player(player_id, filesp[names[k]]));
			return;
		}
		content = explode(read_file(filesp[names[i]]), "\n");
		long_flag = 0;
		enter_receive = 0;
		filename = to_player(player_id, filesp[names[i]]);
		dstfile = "// File(" + to_player(player_id, filesp[names[i]]) + ")" + 
			  " of " + player_id + "'s room\n// Create by LUBAN written by Doing Lu\n";
		for (k = 0; k < sizeof(content); k++)
		{
			if (strsrch(content[k], "LONG") != -1)  // �鵽��һ��LONG��־
			{
				long_flag = ! long_flag;
				if (! long_flag)
				{
					// ����µ�long����
					desc = descsp[names[i]];
					if (! desc || desc == "")
					{
						// ������ȱʡ����
						ob = get_object(filesp[names[i]]);
						desc = ob->query("default_long");
						if (! desc) desc = replace_string(ob->query("long"), "\n", "");
					}
					desc = replace_string(desc, "ROOM_POSITION", position_short);
					desc = sort_desc(me, desc);
					dstfile += "\tset(\"long\", \"" + desc + "\");\n";
				}
				continue;
			}
			// �����LONG���������
			if (long_flag) continue;

			// ����þ������/**/�����
			if (strsrch(content[k], "/**/") != -1) continue;
			if (strsrch(content[k], "/* EXAMPLE */") != -1) continue;
			if (strsrch(content[k], "/* example */") != -1) continue;

			// ȥ������е�//**
			content[k] = replace_string(content[k], "//**", "    ");

			// ����þ���//��ͷ����ʾע�ͣ������
			if (content[k][0..1] == "//") continue;

			// �жϸ��ļ��Ƿ�������ļ��������ļ��Ƿ��е�������(position)�ĳ���
			if (strsrch(content[k], "/d/room/xiaoyuan") != -1)
				entry = filename;

			// �滻����е�ROOM/KEY, OWNER, position
			content[k] = replace_string(content[k], "ROOM_KEY", room_key);
			content[k] = replace_string(content[k], "ROOM_OWNER_ID", player_id);
			content[k] = replace_string(content[k], "ROOM_OWNER", room_owner);
			content[k] = replace_string(content[k], "ROOM_NAME", room_name);
			content[k] = replace_string(content[k], "ROOM_ID", room_id);
			content[k] = replace_string(content[k], "ROOM_POSITION", position_short);
			content[k] = replace_string(content[k], "OUTDOORS", outdoors);
			content[k] = replace_string(content[k], "/d/room/xiaoyuan", position);

			// ��Ӹ����
			if (content[k] == "")
				enter_receive ++;
			else 
				enter_receive = 0;
			if (enter_receive > 1) continue;
		
			dstfile += content[k] + "\n";
		}
		if (long_flag)
		{
			write("�ļ�:" + filesp[names[i]] + "��ʽ����"
			      "LONG��ƥ�䣬�������ɷ��ݣ������ʦ��ϵ��\n");
			// ɾ���Ѿ��������ļ�
			for (k = i - 1; k >= 0; k--)
				rm(to_player(player_id, filesp[names[k]]));
			return;
		}

		// д�����
		seteuid(getuid());
		rm(filename);
		assure_file(filename);
#if 0
		if (wiz_level(this_player()) >= WIZLEVEL)
		{
			write(HIY "Try to write file:" + filename + ""NOR"\n");
			write(dstfile);
			write(HIC "\nOk."NOR"\n");
		}
#endif
		// avoid the old object's data in dbase
		DBASE_D->clear_object(filename[0..<3]);
		write_file(filename, dstfile);

		dstfile = "";
	}

	// �ڽ����������ڵ���ҵķ���
	if (! entry || entry == "")
	{
		message("vision", "\n����һ�ᣬ³����ڵ����������ĵ�"
				  "���˻�����³�������˵�����ǹ��£�"
				  "��Ȼ�Ҳ�����ڣ���ȥ������ʦ������"
				  "��ô��ģ�\n", environment());
		// ɾ���Ѿ��������ļ�
		for (k = i - 1; k >= 0; k--)
			rm(to_player(player_id, filesp[names[k]]));
		return;
	}

	ob = get_object(position);
	if (! ob || ! ob->create_room(room_name, room_id, entry))
	{
		message("vision", "\n����һ�ᣬ³����ڵ����������ĵ�"
				  "���˻�����\n³��һ��ù����������˵"
				  "����а���ˣ���Ȼû�н��ɷ��ӣ�\n��"
				  "�̵�ͷ���ҹ�������һǧ���껹��ͷ"
				  "�����������£�\n",
				  environment());
		// ɾ���Ѿ��������ļ�
		for (k = i - 1; k >= 0; k--)
			rm(to_player(player_id, filesp[names[k]]));
		return;
	}
	message("vision", "\n������³����ڵ�����Ȼ������\n"
			  "³��ϲ�����Ǻǣ����ݽ����ˣ�һ��"
			  "˳������ϲ��ϲ��\n", environment());
	ob->save();

	// ������ҷ��ݵ�Կ���ļ�
	filename = file_dir(player_id) + "key.c";
	dstfile = "// File(" + filename + ")" + 
		  " of " + player_id + "'s key\n// Create by LUBAN written by Doing Lu\n";
	dstfile += @KEY

#include <ansi.h>

inherit ITEM;

string query_autoload() { return "1"; }

void create()
{
	set_name(YEL "KEY_NAME" NOR, ({ "key", "KEY_ID" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", @LONG
KEY_DESCRIPTION��
����ԭ��Կ�ס�
LONG );
		set("unit", "��");
		set("no_pawn", 1);
		set("no_sell", 1);
		set("item_make", 1);
		set("value", 1);
	}
}
KEY;
	// �滻Կ�����ƣ�ID������
	desc = "һ����������" + room_name + "(" + room_id + ")��Կ��";
	dstfile = replace_string(dstfile, "KEY_DESCRIPTION", desc);
	dstfile = replace_string(dstfile, "KEY_NAME", me->query("name") + "�ҵ�Կ��");
	dstfile = replace_string(dstfile, "KEY_ID", room_key);

	seteuid(getuid());
	rm(filename);
	assure_file(filename);
	write_file(filename, dstfile);

	// ����Կ��
	ob = clone_object(filename);
	message_vision("³���ó�һ��Կ�ף���$N˵��ŵ������Կ�ף��պ��ˣ�"
		       "���Ƕ��˿��Ե�����������һ�ѡ�\n", me);
	ob->move(this_object());
	command("give key to " + me->query("id"));

	// ɾ��³�ദ��¼�ı�
	delete("form/" + player_id);
	save();

	// ������ҵ����ݿ�
	me->set("private_room/build", 1);	       // �Ѿ���������
	me->set("private_room/position", position);     // �������ڵ�λ��
	me->set("private_room/entry", entry);	   // ������ڴ����ļ�·��
	me->set("private_room/name", room_name);	// ���ݵ�����
	me->set("private_room/id", room_id);	    // ���ݵ�ID
	me->set("private_room/type", room_type);	// ���ݵ�����
	me->set("private_room/key_no", 1);	      // ʹ��ԭ��Կ��
	me->save();

	command("chat* heihei");
	return;
}

// �����ұ��淿���ļ���·����
private string file_dir(mixed me)
{
	string dir;

	dir =  DATA_DIR + "room/";
	if (objectp(me))
		dir += me->query("id") + "/";
	else
	if (stringp(me))
		dir += me + "/";
	else
		return 0;

	return dir;
}

// ��ԭ�ͷ����ļ���ת����Ϊ�û����ݵ��ļ���
private string to_player(string player_id, string file_name)
{
	string typestr;
	string retstr;

	sscanf(file_name, "/d/room/%s/%s", typestr, retstr);
	return file_dir(player_id) + retstr;
}

// ����Ϊ�˼ӿ������ٶ�ʹ�õĺ꺯��
// �ж��ײ����ַ����Ƿ���ͬ(�ַ���1������ַ���2��)
#define IS_HEAD(s1,s2)    (s1[i..i + strlen(s2) - 1] == s2)
// �ж��ַ����ײ��Ƿ�ΪӢ�ı�����
#define IS_HEAD_ESIGH(s1) (s1[i] == '.' || s1[i] == '!' || s1[i] == ';' || s1[i] == ',' || s1[i] == ':')
// �ж��ַ����ײ��Ƿ�Ϊ���ı�����
#define IS_HEAD_CSIGH(s1) (s1[i..i + 1] == "��" || s1[i..i + 1] == "��" || s1[i..i + 1] == "��" || s1[i..i + 1] == "��" || s1[i..i + 1] == "��")
// �ж��ַ����ײ��Ƿ��������ַ�
#define IS_HEAD_CHN(s1)   (s1[i] > 160)

// �淶������Ϣ
// ���������ҪΪ���û������������Ϣ��ӻس�������
private string sort_desc(mixed me, string desc)
{
	object pos;
	string player_id;
	string ids;
	string room_name;
	string room_owner;
	string position_short;

	if (! desc || desc =="")
		return 0;

	if (stringp(me)) player_id = me; else
	if (objectp(me)) player_id = me->query("id"); else
			 return 0;
	if (mapp(query("form/" + player_id)))
	{
		ids = "form/" + player_id + "/";
		room_name = query(ids + "name");
		room_owner = query(ids + "player");
		pos = get_object(query(ids + "position"));
		if (pos) position_short = pos->short(); else
			 position_short = "��֪�δ�";
	} else
	if (objectp(me))
	{
		ids = "contract/luban/";
		room_name = me->query_temp(ids + "name");
		room_owner = me->query("name");
		pos = get_object(me->query_temp(ids + "position"));
		if (pos) position_short = pos->short(); else
			 position_short = "��֪�δ�";
	} else
		return 0;

	// �滻����е�ROOM_OWNER, position
	desc = replace_string(desc, "ROOM_NAME", room_name);
	desc = replace_string(desc, "ROOM_OWNER", room_owner);
	desc = replace_string(desc, "ROOM_POSITION", position_short);
	return sort_string(desc, 60, 4);
}
