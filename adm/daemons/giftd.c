
#include <ansi.h>
inherit F_DBASE;

static int chunjie_flag;

mapping *gift_data = ({
	([
		"name"		:	"�Ͷ���",
		"month"		:	5,
		"daymin"	:	1,
		"daymax"	:	1,
		"says"		:	HIY"�Ͷ��ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_may" }),
	]),
	([
		"name"		:	"�����",
		"month"		:	5,
		"daymin"	:	30,
		"daymax"	:	30,
		"says"		:	HIY"����ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_duanwu" }),
	]),
	([
		"name"		:	"�����",
		"month"		:	10,
		"daymin"	:	4,
		"daymax"	:	8,
		"says"		:	HIY"����ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/shizhe/yuebing1", "/clone/shizhe/yuebing2", "/clone/shizhe/yuebing3" }),
	]),
	([
		"name"		:	"�����",
		"month"		:	10,
		"daymin"	:	1,
		"daymax"	:	3,
		"says"		:	HIY"����ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_guoqing" }),
	]),
	([
		"name"		:	"ʥ����",
		"month"		:	12,
		"daymin"	:	22,
		"daymax"	:	24,
		"says"		:	HIY"ʥ���ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_christmas" }),
	]),
	([
		"name"		:	"Ԫ��",
		"month"		:	1,
		"daymin"	:	1,
		"daymax"	:	3,
		"says"		:	HIY"Ԫ�����ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_yuandan" }),
	]),
	([
		"name"		:	"����1",
		"month"		:	2,
		"daymin"	:	15,
		"daymax"	:	21,
		"says"		:	HIY"���ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_chunjie" }),
	]),
/*
	([
		"name"	:	"����2",
		"month"	:	2,
		"daymin"	:	1,
		"daymax"	:	3,
		"says"		:	HIY"���ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_chunjie" }),
	]),
*/
	([
		"name"		:	"Ԫ��",
		"month"		:	3,
		"daymin"	:	2,
		"daymax"	:	2,
		"says"		:	HIY"Ԫ���ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_yuanxiao" }),
	]),
	([
		"name"		:	"����",
		"month"		:	1,
		"daymin"	:	24,
		"daymax"	:	24,
		"says"		:	HIY"���˽ڵ��ˣ�ָ��MUDΪ��׼����һ��С���ף�����տ��֣�"NOR,
		"items"		:	({ "/clone/gift/gift_laba" }),
	]),

});

mapping chunjie_online = ([
		"month"		:	2,
		"daymin"	:	4,
		"daymax"	:	10,
		"hmin"		:	18,
		"hmax"		:	22,
		"says"		:	HIY"�����ڼ�ָ��MUDΪ���ߵ��������׼����һ��С���ף���������֣�"NOR,
		"yuanbao"	:	200,
	]);

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "���վ���");
	CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������");
	set_heart_beat(20);
}

void check_gift(object me)
{
	mixed today;
	int i;
	object obj;

	today = localtime(time());
	for(i=0;i<sizeof(gift_data);i++)
	{
		if( (today[4]+1)==gift_data[i]["month"] && today[3]>=gift_data[i]["daymin"] && today[3]<=gift_data[i]["daymax"] )
		{
			if( !me->query("holiday/"+gift_data[i]["name"]+"/day"+today[3]) )
			{
				if(!sizeof(gift_data[i]["items"])) return;
				obj = new(gift_data[i]["items"][random(sizeof(gift_data[i]["items"]))]);
				obj->move(me);
				tell_object(me,gift_data[i]["says"]+"\n");
				tell_object(me,"������һ"+obj->query("unit")+obj->query("name")+"��\n");
				me->set("holiday/"+gift_data[i]["name"]+"/day"+today[3],1);
			}
		}
		else
		{
			me->delete("holiday/"+gift_data[i]["name"]);
		}
	}
}

void heart_beat()
{
	mixed today;
	object ob,*obs;
	int time = time();

	today = localtime(time);

	if( (today[4]+1)==chunjie_online["month"] && today[1]==0 && today[3]>=chunjie_online["daymin"] && today[3]<=chunjie_online["daymax"]
		&& today[2]>=chunjie_online["hmin"] && today[2]<=chunjie_online["hmax"] )
	{
		if ( !chunjie_flag )
		{
			obs = filter_array(all_interactive(),(: living($1) 
						&& $1->query_skill("force") >= 200
						&& $1->query_skill("dodge") >= 200
						&& $1->query_skill("parry") >= 200
						&& !wizardp($1) :));
			if(sizeof(obs)<1) return;
			ob = obs[random(sizeof(obs))];
			ob->add("yuanbao",200);
			chunjie_flag = 1;
			CHANNEL_D->do_channel(this_object(), "chat", chunjie_online["says"]);
			CHANNEL_D->do_channel(this_object(), "chat", ob->query("name")+"���200Ԫ�����˽�����");
			log_file("chunjie", sprintf("%s:%s(%s)��ô�������Ԫ��������\n",ctime(time()),ob->query("name"),ob->query("id")));
		}
	}
	else chunjie_flag = 0;
}
