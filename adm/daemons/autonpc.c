//autonpc.c
//by luoyun
#include <ansi.h>

inherit F_DBASE;
#include <localtime.h>

mapping room_place = ([
	"����ɽ"		: "/d/baituo/",
	"����"			: "/d/beijing/",
	"����" 			: "/d/changan/",
	"����"			: "/d/city/",
	"�ɶ�"			: "/d/city3/",
	"����"			: "/d/dali/",
	"����ɽ" 		: "/d/emei/",
	"��ɽ"			: "/d/foshan/",
	"ؤ��" 			: "/d/gaibang/",
	"����"			: "/d/fuzhou/",
	"����"			: "/d/guanwai/",
	"����ɽׯ"	: "/d/guiyun/",
	"��Ĺ" 			: "/d/gumu/",
	"����"			: "/d/hangzhou/",
	"��ľ��"		: "/d/heimuya/",
	"��ɽ" 			: "/d/hengshan/",
	"��ɽ"			: "/d/henshan/",
	"�ƺ�"			: "/d/huanghe/",
	"��ɽ��"		: "/d/huashan/",
	"���չ�"			: "/d/lingjiu/",
	"����"			: "/d/lingzhou/",
	"÷ׯ"			: "/d/meizhuang/",
	"����" 			: "/d/mingjiao/",
	"���ɽ"		: "/d/qingcheng/",
	"ȫ����" 		: "/d/quanzhen/",
	"Ȫ��" 			: "/d/quanzhou/",
	"������" 		: "/d/shaolin/",
	"������"		: "/d/shenlong/",
	"��ɽ"			: "/d/songshan/",
	"����"			: "/d/suzhou/",
	"̩ɽ"			: "/d/taishan/",
	"�һ���"		: "/d/taohua/",
	"������"		: "/d/tianlongsi/",
	"��ٹ�"		: "/d/wanjiegu/",
	"�䵱ɽ"		: "/d/wudang/",
	"���͵�"		: "/d/xiakedao/",
	"����"			: "/d/xiangyang/",
	"��ң��"		: "/d/xiaoyao/",
	"���޺�" 		: "/d/xingxiu/",
	"Ѫ����" 		: "/d/xuedao/",
	"ѩɽ" 		: "/d/xueshan/",
	"������" 		: "/d/yanziwu/",
]);

string *special_list = ({
	"/clone/book/wuji1",
	"/clone/book/wuji2",
	"/clone/book/wuji3",
	"/clone/book/wuji4",
	"/clone/book/qiankun_book",
	"/clone/book/six_book",
	"/clone/book/yijinjing",
	"/clone/book/lbook4",
	"/clone/book/jiuyin1",
	"/d/tulong/obj/zhenjing",
	"/clone/book/ling1",
	"/clone/book/ling2",
	"/clone/book/ling3",
	"/d/tulong/obj/tulongdao",
	"/d/tulong/obj/yitianjian",
	"/clone/weapon/zhenwu",
	"/clone/weapon/xtbishou",
	"/clone/weapon/jsbaojia",
});

object load_room_place(string file_dir)
{
	string *file, bin_dir, path;
	int max, get_an;
	object room;

	bin_dir = file_dir;
		
	if (! bin_dir)
		bin_dir = "/binaries" + file_dir;

	if ( file_size(bin_dir) != -2 ) return 0;
	file = get_dir(bin_dir, -1);

	if ( !(max = sizeof(file)) ) return 0;

	get_an = random(max);
	path = bin_dir + file[get_an][0];
	if ( file_size(path) <= 0 ) return 0;

	if (room=find_object(path))
		return room;
	else
		return load_object(path[0..<3]);
}

int ok = 0;
int ok1 = 0;
string path_where=0;

void create()
{
	seteuid(getuid());
	set("channel_id", "����ϵͳ");
	CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������"NOR);
	set_heart_beat(20);
}

int clean_up()
{
	return 1;
}
object do_copy()
{
	object room;
	string *strtemp, locastr, exit;
	int temp, i1, i;
	
	//ȷ��λ�� 
	strtemp = keys(room_place);
	i1 = sizeof(strtemp);
	temp = random(i1);
	locastr = room_place[strtemp[temp]];
	room = load_room_place(locastr);
	path_where = strtemp[temp];
	
	if( objectp(room) )
	{
		exit = room->query("exits"); 
		if ( !room->query("short") || !mapp(exit) || !sizeof(exit) || !room->query("outdoors") || room->query("no_fight")) 
			return do_copy();
	} 

	if ( !objectp(room) )
		return do_copy();
	else
		return room;
}

void clear_special()
{
	int i,k;
	object *list,ob;

	for(i=0;i<sizeof(special_list);i++)
	{
		list = children(special_list[i]);
		if(!list||!sizeof(list)) continue;
		for(k=0;k<sizeof(list);k++)
		{
			if((ob=environment(list[k]))&&playerp(ob))
			{
				tell_object(ob,"ϵͳ������Ʒˢ�£������ϵ�"+list[k]->short()+"��ʧ�ˣ�\n");
				destruct(list[k]);
			}
		}
	}
}

void check_time()
{
	int GMT = time();
	string d, times;
	int h, s;
	object room, ob;

	times = ctime(GMT);
	//Sun(������) Mon(����һ)  Tue(���ڶ�)  Wed(������)  Thu(������)  Fri(������)  Sat(������)
	d = times[0..2];//����
	h = to_int(times[10..12]);//ʱ
	s = to_int(times[14..15]);//��

	if ((s == 50) && !ok) {
		if (!room = do_copy())
			room = do_copy();
		else {
			ob = new("/clone/npc/feizei");
			if (ob->move(room)) {
				message("channel", HIR"���ٸ���:"HIY"��˵�з�����"+HIG+path_where+HIY"һ�����֣��뿴�غ��ԼҲ��"NOR"\n", users());
				CHANNEL_D->do_channel( this_object(), "sys", "���������ˡ�"+ZJURL("cmds:goto "+file_name(ob))+"�ɹ�ȥ"+NOR"��");
				ok = 1;
				call_out("remove_npc", 120, ob);
			} else
				CHANNEL_D->do_channel( this_object(), "sys", "��������ʧ�ܡ�"NOR);
		}
	}

	if ((h == 18) && (s == 0) && !ok1) {
		clear_special();
		ok1 = 1;
	}

	if (s!=50) ok = 0;
	if (!(h==18&&s==0)) ok1 = 0;
}

void remove_npc(object ob)
{
	if (ob) {
		ob->force_me("say ���ط����ûʲô��ˮ���̣����ǻؼҰɣ�\n");
		destruct(ob);
	}
}

protected void heart_beat()
{	
	check_time();
}