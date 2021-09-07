// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <config.h>
#include <getconfig.h>

#define MUDLIST_CMD     "/cmds/usr/mudlist"
#define REBOOT_CMD      "/cmds/arch/reboot"

inherit F_DBASE;

static int wiz_lock_level = 0;

static string *movie;

string *banned_name = ({
    "��", "��", "��", "��", "��", "��","����",
    "��", "ү", "��", "��","����","����","�ٲ�","fuck","����","����","�ڽ�","�Խ�","����","����",
    "ʺ", "��", "��","����","����","��ү","����","����","����",
"�Լ�","ɱ��","����","ѩ��","��ң","����","����","����","����","���","ĳ��","ʬ��",
"����","�ܹ�","����","����","��ʦ","�ſ�","���","��","�齣","���ִ���","����ͨ","����",
"������","�̿�","����","��ʦ","���","ͷ­","ɱ�˷�",
// Mud ������������
"��ɽ","��ɽ","��ɽ","��ɽ","̩ɽ","ѩɽ","��ɽ","��ɽ","����","�置","����","��ԭ",
"�Ͻ�","����","�ƺ�","�й�","�л�","����ɽ","����ɽ","����ɽ","�䵱ɽ","����ɽ",
"����","�һ���","��ľ��",
"����","ؤ��","����","����","��Ĺ","ȫ��","����","����","����","�һ�","����",
"������","������","�嶾��","����","а��","��������","�������","�ٸ�","����",
"������","�䵱��","���ư�","��ͨ����","������","����Ľ��","��Ĺ��","��ɽ��","��ɽ��",
"����","������","������",
// ��Ҫ��������
"��ӹ","��Сƽ","������","ë��","���Ż�","�ʵ�", "����","����", "��ϯ", "ϰ��ƽ", "���ǿ",
 "����Ա", "��ʦ", "�ɲ�",
// С˵����
"������","���޼�","����","���","�����","���","���˷�","ΤС��","Ԭ��־","��һ��",
"�¼���","����","����","�Ƿ�","����","��������","ŷ����","���߹�","��ҩʦ","�λ�ү",
"һ�ƴ�ʦ","������","�ܲ�ͨ","����","������","�������",
// �໰
"ͳһ","����","�����о�","���ִ�","����","�����","ȥ���","������","������","����",
"�쵰","����","ɱ��","����","ǿ��","��Ů","̨��","�쵼","����","ƨ��","ƨ��","����",
"��ƨ","����","����","���","��Ѿ","����","����","����","ɵ��","����","����","�Ҳ�",
"̫��","�¹�","�˸�","����","��", "����", "����", "�ּ�", "��", "����", "����",
//��������
"��Ů","����",

});

// �ڲ����õĺ���
private void get_user(string arg, object ob);
private void get_char(string arg, object ob);
void jiance(string arg,object ob,string str);
private void init_new_player(object user);

// ���Ա��ⲿ���õĺ���
object  make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg, int maxlen);

void create() 
{
	seteuid(ROOT_UID);
	set("channel_id", "����");
}

void logon(object ob)
{
	string str;
	if (BAN_D->is_banned(query_ip_name(ob)) == 1) {
		write(ZJTMPSAY"��ĵ�ַ�ڱ� MUD ���ܻ�ӭ��\n");
		destruct(ob);
		return;
	}
	write("\n");
	str = crypt(ZJKEY,0);
	write("ver1.0,"+str+"\n");
	input_to("jiance",ob,str);
}

void jiance(string arg,object ob,string str)
{
	if(!arg)
	{
		input_to("jiance",ob,str);
		return;
	}
	else if (arg!=crypt(ZJKEY,str[2..3])&&arg!="zjmDMaIpOvxdb")
	{
		write("�ͻ��˷Ƿ�\n");
		log_file( "logins", sprintf("%s:%s\n",arg,str) );
		destruct(ob);
		return;
	}
	if(arg=="zjmDMaIpOvxdb") ob->set_temp("web_log",1);
	write("�汾��֤�ɹ�\n");
	input_to("get_user", ob);
}

private void get_user(string arg, object ob)
{
	//arg,�˺ŨU����U���ĨUemail��
	object old_link,user;
	string *myinfo,ip,email;

	if( !arg||arg=="") {
		input_to("get_user", ob);
		return;
	}

	myinfo = explode(arg,"�U");

	if( sizeof(myinfo)!=4 ) {
		write(ZJTMPSAY"δ֪����������s������\n");
		input_to("get_user", ob);
		return;
	}

	if( !check_legal_id(lower_case(myinfo[0]))) {
		//0001��ID���Ϸ�
		input_to("get_user", ob);
		return;
	}
/*
	if( (crypt(ZJKEY,myinfo[0])+crypt(ZJKEY,myinfo[1]))!=myinfo[2] && !ob->query_temp("web_log")) {
		write(ZJTMPSAY"�˺�����У����������ԡ�����\n");
		input_to("get_user", ob);
		return;
	}
*/
	myinfo[0] = lower_case(myinfo[0]);

/*
	if (1) {
		write(ZJTMPSAY"��������ʱ���ܵ�½��\n");
		input_to("get_user", ob);
		return;
	}
*/
	if (wiz_level(myinfo[0]) < wiz_lock_level)
        {
		write(sprintf(ZJTMPSAY"�Բ���%s����ά���У����Ժ��¼������\n",LOCAL_MUD_NAME()));
		input_to("get_user",ob);
		return;
	}

	if( (string)ob->set("id", myinfo[0]) != myinfo[0]) {
		write(ZJTMPSAY"δ֪����������i������\n");
		input_to("get_user", ob);
		return;
	}

	if(sscanf(myinfo[3],"%s&%s",ip,email)==2)
	{
		ob->set_temp("last_ip",ip);
		ob->set("email",email);
	}
	else
		ob->set("email",myinfo[3]);

	if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) 
	{
		if( !ob->restore() ) 
		{
			write(ZJTMPSAY"����浵�������⡣����\n");
			input_to("get_user", ob);
			return;
		}
		if (! stringp(myinfo[1]) || crypt(myinfo[1], ob->query("password"))!=ob->query("password"))
		{
			write(ZJTMPSAY"��Ϸ�����������ϵ����Ա��\n");
			destruct(ob);
			return;
		}
	}
	else 
		ob->set("body", USER_OB);

	if( (string)ob->set("password",crypt(myinfo[1],"zj")) != crypt(myinfo[1],"zj")) {
		write(ZJTMPSAY"δ֪����������p������\n");
		input_to("get_user", ob);
		return;
	}

	write("\n");

	user = find_body(ob->query("id"));
	if (user) {
		old_link = user->query_temp("link_ob");
		if( old_link ) {
			if(interactive(user))
			{
				tell_object(user, RED"����˺��ڱ𴦵�¼���㱻�������ˣ�\n");
				exec(old_link, user);
			}
			destruct(old_link);
		}
		//0007����½�ɹ�
		write(SYSY"0007\n");
		write(ZJTMPSAY"��¼�ɹ������ڼ������硣����\n");
		reconnect(ob, user);
		return;
	}
	if( objectp(user = make_body(ob)) ) {
		user->set_temp("link_ob",ob);
		if( file_size(user->query_save_file() + __SAVE_EXTENSION__) >= 0 ){
			if( user->restore() ) {
				//////0007����½�ɹ�
				write(SYSY"0007\n");
				write(ZJTMPSAY"��¼�ɹ������ڼ������硣����\n");
				enter_world(ob, user);
				return;
			} else {
				write(ZJTMPSAY"����浵�������⡣����\n");
				input_to("get_user", ob);
				return;
			}
		}
	}
	destruct(user);
	//�뽨����ɫ
	write(SYSY"0008\n");
	input_to("get_char", ob);
}

private void get_char(string arg, object ob)
{
	//arg,�Ա�Uͷ��U�ǳơ�
	object user;
	string *myinfo,result;

	if( !arg||arg=="") {
		input_to("get_char", ob);
		return;
	}

	myinfo = explode(arg,"�U");
	if(sizeof(myinfo)!=3){
		write(ZJTMPSAY"�����������ԡ�\n");
		input_to("get_char", ob);
		return;
	}

	if( !check_legal_name(myinfo[2],8) ) {
		//0009���ǳƲ�����Ҫ��
		input_to("get_char", ob);
		return;
	}
	if (stringp(result = NAME_D->invalid_new_name(myinfo[2])))
	{
		write(ZJTMPSAY"�Բ���" + result+"\n");
		input_to("get_char", ob);
		return;
	}

	ob->set("purename", myinfo[2]);
	ob->set("name", myinfo[2]);
	if( !objectp(user = make_body(ob)) )
		return;
	user->set("str", 10);
	user->set("dex", 10);
	user->set("con", 10);
	user->set("int", 10);
	user->set("kar", 10);
	user->set("per", 10);
	user->set("gender", myinfo[0]);
	user->set("img", myinfo[1]);
	init_new_player(user);
	VIP_D->restore_vdata(user);
//0007����½�ɹ�
	write(SYSY"0007\n");
	call_out("enter_world",1,ob, user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	seteuid(getuid());
	user = new(USER_OB);
	if (! user)
	{
		write("���ڿ������������޸�ʹ��������ĳ�ʽ���޷����и��ơ�\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set("surname", ob->query("surname"));
	user->set("purename", ob->query("purename"));
	user->set_name( 0, ({ ob->query("id")}) );
	return user;
}

private void init_new_player(object user)
{
	// ��ʼ����Ҫ����
	user->set("title", "��ͨ����");
	user->set("birthday", time() );
	user->set("potential", 99);
	user->set("food", (user->query("str") + 10) * 10);
	user->set("water", (user->query("str") + 10) * 10);
	user->set("channels", ({ "chat", "rumor", "party",
				 "bill", "sos", "family",
				 "ic", "rultra" }));

	// ��¼����
	NAME_D->map_name(user->query("name"), user->query("id"));

	// ���ñ�Ҫ�Ļ�������
	user->set("env/wimpy", 60);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, shoe, room, login_ob;
	string startroom;
	string ipname;

	if(! is_root(previous_object()))
		return;

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	if(ob->query_temp("web_log"))
	{
		user->set_temp("web_log",1);
		if(ob->query_temp("last_ip"))
			user->set("last_ip",ob->query_temp("last_ip"));
	}
	else
	{
		user->delete_temp("web_log");
		user->set("last_ip",query_ip_name(ob));
	}

	log_file("loginip",ctime(time())+":"+user->query("id")+"��"+user->query("last_ip")+"������Ϸ��\n");
	ob->set("registered", user->query("registered"));

	if (interactive(ob)) exec(user, ob);

	write("\nĿǰȨ�ޣ�" + wizhood(user) + "\n");

	user->setup();
	if (user->query("age") == 14)
	{
		user->set("food", user->max_food_capacity());
		user->set("water", user->max_water_capacity());
	}

	user->save();
	user->set("last_save", time());
	user->force_me("mycmds");
	ob->save();

	// check the user
	UPDATE_D->check_user(user);
	TOP_D->map_user(user);

	if (! silent)
	{
		if (! user->query("registered"))
			color_cat(UNREG_MOTD);
		else
			color_cat(MOTD);

		write("�����߽�����" + LOCAL_MUD_NAME() + "��\n\n");

		if (! user->query("registered") || ! stringp(user->query("character")))
		{
			if (user->is_ghost())
				user->reincarnate();
			user->set("startroom", REGISTER_ROOM);
		} else
		if (! stringp(user->query("born")))
		{
			if (user->is_ghost())
				user->reincarnate();
			user->set("startroom", BORN_ROOM);
		}

		if (user->is_in_prison())
			startroom = user->query_prison();
		else
		if (user->is_ghost())
			startroom = DEATH_ROOM;
		else
		if (! stringp(startroom = user->query("startroom")) ||
		    file_size(startroom + ".c") < 0)
			startroom = START_ROOM;

		if ((user->query("str")+user->query("con")+user->query("dex")+user->query("int"))>(100+user->query("relife/zhuanshi")*4+user->query("gift/lighting")+user->query("level")/10)
		&& user->query("id")!="chong1")
		{
			user->set("startroom", "/d/death/block");
			startroom = "/d/death/block";
		}

		if (present("chuwu dai 2", user))
		{
			user->set("startroom", "/d/death/block");
			startroom = "/d/death/block";
		}

		if ( (user->query("experience")-user->query("learned_experience"))>660000 && user->query("zjvip/all_pay")<31500)
		{
			user->set("startroom", "/d/death/block");
			startroom = "/d/death/block";
		}

		if (! catch(load_object(startroom)))
			user->move(startroom);
		else
		{
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		tell_room(startroom, user->query("name") + "���߽���������硣\n", ({user}));
	}

	login_ob = new(LOGIN_OB);
	login_ob->set("id", user->query("id"));
	login_ob->restore();
	if (login_ob->query("registered"))
	{
		if (! intp(login_ob->query("login_times")))
		{
			write(NOR "\n���ǵ�һ�ι���" + LOCAL_MUD_NAME() + "��\n");
			login_ob->set("login_times", 1);
			// show rules
		} else
		{
			login_ob->add("login_times", 1);
			write("\n���ϴι���" + LOCAL_MUD_NAME() + "�� " + HIG + ctime(login_ob->query("last_on")) + NOR + " �� " + HIR +
				login_ob->query("last_from") + NOR + " ���ӵġ�\n");
		}
	}

	destruct(login_ob);

	CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)��%s���߽��롣",user->name(), user->query("id"),
					(ipname = query_ip_number(user)) ? ipname : "δ֪�ص�"));

	if (wizhood(user) != "(admin)" && EXAMINE_D->query("log_by/" + user->query("id")))
		user->start_log();
/*
	if(FAMILY_D->query_lunjian_leader()==user->query("id"))
	{
		CHANNEL_D->do_channel(this_object(), "chat",sprintf("����������%s(%s)���߽�����Ϸ��",user->name(), user->query("id")));
		shout(sprintf(ZJSIZE(22)+HBGRN+HIR" �������� "ZJSIZE(22)+HBCYN+HIR"%s������Ϸ��"NOR"\n",user->name()));
		write(sprintf(ZJSIZE(22)+HBGRN+HIR" �������� "ZJSIZE(22)+HBCYN+HIR"%s������Ϸ��"NOR"\n",user->name()));
	}
	else 
*/
	if(FAMILY_D->query_family_leader(user->query("family/family_name"))==user->query("id"))
		CHANNEL_D->do_channel(this_object(), "chat",sprintf("%s��ϯ����%s(%s)���߽�����Ϸ��",
			user->query("family/family_name"), user->name(), user->query("id")));

	NEWS_D->prompt_user(user);
	GIFT_D->check_gift(user);
	if ((user->query("qi") < 0 || user->query("jing") < 0) && living(user))
		user->unconcious();
}

varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	if(ob->query_temp("web_log"))
		user->set_temp("web_log",1);
	else
		user->delete_temp("web_log");
	ob->set_temp("body_ob", user);
	exec(user, ob);

	user->reconnect();
	if( !silent && (! wizardp(user) || ! user->query("env/invisible"))) {
		tell_room(environment(user), user->query("name") + "�������߻ص�������硣\n",
		({user}));
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s[%s]��%s�������߽��롣", user->query("name"),
			user->query("id"), query_ip_number(user)));
	user->force_me("mycmds");
	user->force_me("look");
}

int check_legal_id(string id)
{
	int i;

	id = lower_case(id);

	i = strlen(id);

	if( (i<4||i>20) && (string)SECURITY_D->get_status(id) == "(player)" ) {
		write(ZJTMPSAY"�Բ������ID���Ȳ�����Ҫ��(4-20)��\n");
		return 0;
	}

	if( id[0]<'a' || id[0]>'z' ) {
		write(ZJTMPSAY"�Բ������ID������Ӣ����ĸ��ͷ��\n");
		return 0;
	}
	while(i--)
	{
		if( !((id[i]>='a' && id[i]<='z')||id[i]=='_'||(id[i]>='0' && id[i]<='9')) ) {
			write(ZJTMPSAY"�Բ������IDֻ����Ӣ����ĸ��������ּ���_������ϡ�\n");
			return 0;
		}
	}

	return 1;
}

int check_legal_name(string name, int maxlen)
{
	int i;

	i = strlen(name);
	
	if ((strlen(name) < 4) || (strlen(name) > maxlen))
	{
		write(ZJTMPSAY"�Բ������������������̫����̫�̡�\n");
		return 0;
	}

	if (! is_chinese(name))
	{
		write(ZJTMPSAY"�Բ��������á����ġ�ȡ���֡�\n");
		return 0;
	}

	for(i=0;i<sizeof(banned_name);i++)
	{
		if (strsrch(name,banned_name[i]) != -1)
		{
			write(ZJTMPSAY"�Բ��������в��ܰ�����"+banned_name[i]+"����\n");
			return 0;
		}
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	foreach(ob in body) if (getuid(ob) == name) return ob;
	return 0;
}

int set_wizlock(int level)
{
	if (wiz_level(this_player(1)) <= level)
		return 0;

	if (geteuid(previous_object()) != ROOT_UID)
		return 0;

	wiz_lock_level = level;
	return 1;
}

int can_login(int level)
{
	if (level < wiz_lock_level)
		return 0;

	return 1;
}

int howmuch_money(object ob)
{
	int total;
	int total2;
	object gold, silver, coin;

	total = 0;
	total2 = 0;

	gold = present("gold_money",ob);
	silver = present("silver_money",ob);
	coin = present("coin_money",ob);

	if( gold ) total += gold->value();
	if( silver ) total += silver->value();
	if( coin ) total += coin->value();

	total2 = (int)ob->query("balance");
	if (!total2 || total2 < 0) {
		ob->set("balance", 0);
	}
	total=total+total2;
	return total;
}