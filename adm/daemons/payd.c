
#define DEBUGGER "no-one"

#include <net/httpd.h>
#include <net/socket.h>
#include <localtime.h>
inherit F_DBASE;

#define MAXIMUM_RETRIES	10

#define HTTP_HEADER "HTTP/1.0 %s%c"
#define DEFAULT_HEADER "Server: "+MUD_NAME+"/0.2\nMIME-version: 1.0%c"

#define log_info(x, y) log_file(x, ctime(time()) + "\n"); log_file(x, y)

int httpSock;
mapping sockets;
mapping resolve_pending;
string *months,*pay_type;

mapping bad_cmd = BAD_CMD;
mapping access_denied = ACCESS_DENIED;
mapping not_found = NOT_FOUND;
mapping bad_gateway = BAD_GATEWAY;
int persistent;

protected void setup();
void close_connection(int fd);
void set_persistent(int which);

int accesses;

mapping *pay_fix = ({
	([
		"name"	:	"Ԫ����",
		"month"	:	1,
		"daymin"	:	1,
		"daymax"	:	3,
		"pay_fix"	:	30,
	]),
	([
		"name"	:	"�Ͷ���",
		"month"	:	5,
		"daymin"	:	1,
		"daymax"	:	1,
		"pay_fix"	:	10,
	]),
	([
		"name"	:	"�����",
		"month"	:	5,
		"daymin"	:	30,
		"daymax"	:	30,
		"pay_fix"	:	10,
	]),
	([
		"name"	:	"����",
		"month"	:	1,
		"daymin"	:	27,
		"daymax"	:	31,
		"pay_fix"	:	10,
		"payrec"	:	1,
	]),
	([
		"name"	:	"����",
		"month"	:	2,
		"daymin"	:	1,
		"daymax"	:	3,
		"pay_fix"	:	10,
		"payrec"	:	1,
	]),
	([
		"name"	:	"�����",
		"month"	:	10,
		"daymin"	:	1,
		"daymax"	:	8,
		"pay_fix"	:	10,
	]),
	([
		"name"	:	"˫ʮһ",
		"month"	:	11,
		"daymin"	:	11,
		"daymax"	:	11,
		"pay_fix"	:	10,
	]),
	([
		"name"	:	"ʥ����",
		"month"	:	12,
		"daymin"	:	24,
		"daymax"	:	25,
		"pay_fix"	:	10,
	]),
});

int query_accesses()
{
	return accesses;
}

protected void create()
{ 
	set("channel_id", "��ֵ����");
	seteuid( geteuid() );
	accesses = 0;
	set_persistent(1);
	months = ({"1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��","12��"});
	pay_type = ({"���п�","֧����","��ֵ��","�Ƹ�ͨ��","���Ǯ��","���п�","΢��֧��"});
	sockets = ([]);
	resolve_pending = ([]);
	CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�����Ѿ�������");
	call_out("setup", 1);
}

protected void clean_up()
{
} 

protected void setup()
{
	if ((httpSock = socket_create(STREAM, "read_callback", "close_callback")) < 0)
	{
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ���񴴽�ʧ�ܡ�");
		return;
	}
	if (socket_bind(httpSock, ZJPAYPORT) < 0) {
		socket_close(httpSock);
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ����˿ڰ�ʧ�ܡ�");
		return;
	}
	if (socket_listen(httpSock, "listen_callback") < 0) {
		socket_close(httpSock);
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�������ʧ�ܡ�");
	}
}

string http_header(string code)
{
	return sprintf(HTTP_HEADER, code, 10)+sprintf(DEFAULT_HEADER, 10);
}

protected void store_client_info(int fd)
{
	string addr;
	int port;

	sscanf(socket_address(fd), "%s %d", addr, port);
	sockets[fd] = ([
	 "address" : addr,
	 "name" : addr,
	 "port" : port,
	 "time" : time(),
	 "write_status" : EESUCCESS
	]);
}

protected void listen_callback(int fd)
{
	int nfd;

	if ((nfd = socket_accept(fd, "read_callback", "write_callback")) < 0) {
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�����������ʧ�ܡ�");
		return;
	}
	store_client_info(nfd);
}

void write_callback(int fd)
{
	close_connection(fd);
}

string common_date(int t)
{
	mixed* r;

	r = localtime(t);
	return sprintf("%d��%s%02d��%02d:%02d:%02d",
		r[LT_YEAR], months[r[LT_MON]], r[LT_MDAY], r[LT_HOUR],
		r[LT_MIN], r[LT_SEC]);
}

void do_get(string);
void do_post(int, string, string);

protected void read_callback(int fd, string str)
{
	string cmd, args, file, url;
	string *request;
	string tmp, line0;
	string *ips=({
		"47.98.225.51",
		"183.131.217.55",
		"39.108.170.229",
	});
	if (!sizeof(str))
	{
		log_file("pay/err", common_date(time())+":�����ݡ�����("+sockets[fd]["address"]+")\n");
		return;
	}
	if(member_array(sockets[fd]["address"],ips)==-1)
	{
		log_file("pay/err", common_date(time())+":�Ƿ�IP����("+sockets[fd]["address"]+")��\n");
		close_connection(fd);
		return;
	}
	accesses++;
	request = explode(replace_string(str, "\r", ""), "\n");
	line0 = request[0];
	sscanf(line0, "%s /?%s %s", cmd, file, args);
	switch(lower_case(cmd)) {
		case "get":
			close_connection(fd);
			do_get(file);
			break;
		default:
			break;
	}
}

protected void close_callback(int fd)
{
	if (fd == httpSock) {
		log_info(LOG_HTTP_ERR,"��ֵ�����쳣�رգ���������...\n");
		call_out("setup", 1);
	} else {
		map_delete(sockets, fd);
	}
}

protected void close_connection(int fd)
{
	map_delete(sockets, fd);
	socket_close(fd);
}

//��ֵ�������ݴ������������н�����������������������ж�
//�û�id(user_id)��������(order_id)��֧������(pay_type)��֧�����(result_code)��֧�����(amount)��֧��ʱ��(pay_time)
//֧�������0-�ɹ�������ֵ-ʧ��
//֧����XX.XXԪ
//֧�����ͣ�1"���п�",2"֧����",3"��ֵ��",4"�Ƹ�ͨ��",5"���Ǯ��",6"���п�"
//user_id=ranger&order_id=ranger-ranger-1167994550017&pay_type=2&result_code=0&amount=1.00&pay_time=2016-02-01%2014:29:52
protected void do_get(string file)
{
	string *gets,*str,username,userid,mid;
	mapping datas=([]);
	int i,type,amount,rmb,pay_fixed=0;
	object mob,mobj,ob,obj;
	mixed today;

	gets = explode(file,"&");
	for(i=0;i<sizeof(gets);i++)
	{
		if(strsrch(gets[i],"=")!=-1)
		{
			str=explode(gets[i],"=");
			if(sizeof(str)==2)
				datas[str[0]]=str[1];
		}
	}

	if(!VIP_D->query_vips("order")||(member_array(datas["order_id"],VIP_D->query_vips("order"))==-1))
	{
		sscanf(datas["pay_type"],"%d",type);
		sscanf(datas["amount"],"%d",rmb);
		amount = rmb*10;

		VIP_D->add_order(datas["order_id"]);
		datas["user_id"] = lower_case(datas["user_id"]);

		today = localtime(time());
		for(i=0;i<sizeof(pay_fix);i++)
		{
			if( (today[4]+1)==pay_fix[i]["month"] && today[3]>=pay_fix[i]["daymin"] && today[3]<=pay_fix[i]["daymax"] )
			{
				pay_fixed = pay_fix[i]["pay_fix"];
				if(!undefinedp(pay_fix[i]["payrec"]))
					VIP_D->set_gift_payrec(pay_fix[i]["name"]+"/"+datas["user_id"],
						VIP_D->query_gift_payrec(pay_fix[i]["name"]+"/"+datas["user_id"])+rmb);
				break;
			}
		}
		if(amount>=10000) amount += amount*(20+pay_fixed)/100;
		else if(amount>=5000) amount += amount*(10+pay_fixed)/100;
		else if(amount>=100) amount += amount*(5+pay_fixed)/100;
		else amount += amount*pay_fixed/100;

		if(!(obj=find_player(datas["user_id"])))
		{
			ob = new(LOGIN_OB);
			ob->set("id",datas["user_id"]);
			ob->set("body", USER_OB);
			obj = LOGIN_D->make_body(ob);
			destruct(ob);
			if(obj->restore())
			{
				obj->setup();
				username = obj->query("name");
				obj->add("zjvip/all_pay",rmb);
				obj->add("yuanbao",amount);
				if(stringp(mid=obj->query("zjvip/master")))
				{
					if(!(mobj=find_player(mid)))
					{
						mob = new(LOGIN_OB);
						mob->set("id",mid);
						mob->set("body", USER_OB);
						mobj = LOGIN_D->make_body(mob);
						destruct(mob);
						if(mobj->restore())
						{
							mobj->setup();
							mobj->add("zjvip/dizi_pay",rmb);
							mobj->save();
						}
						destruct(mobj);
					}
					else if(mobj)
					{
						mobj->add("zjvip/dizi_pay",rmb);
						mobj->save();
					}
				}
				obj->save();
			}
			destruct(obj);
		}
		else if(obj)
		{
			username = obj->query("name");
			obj->add("zjvip/all_pay",rmb);
			obj->add("yuanbao",amount);
			if(stringp(mid=obj->query("zjvip/master")))
			{
				if(!(mobj=find_player(mid)))
				{
					mob = new(LOGIN_OB);
					mob->set("id",mid);
					mob->set("body", USER_OB);
					mobj = LOGIN_D->make_body(mob);
					destruct(mob);
					if(mobj->restore())
					{
						mobj->setup();
						mobj->add("zjvip/dizi_pay",rmb);
						mobj->save();
					}
					destruct(mobj);
				}
				else if(mobj)
				{
					mobj->add("zjvip/dizi_pay",rmb);
					mobj->save();
				}
			}
			obj->save();
		}
		CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)ͨ��%s��ֵ%sԪ%s��\n",username,datas["user_id"],pay_type[type-1],datas["amount"],datas["result_code"]=="0"?"�ɹ�":"ʧ��"));
		log_file("pay/success", sprintf("%s:%s(%s)ͨ��%s��ֵ%sԪ%s��������%s����ˮ��%s��֧��ʱ��%s��\n",common_date(time()),username,datas["user_id"],pay_type[type-1],datas["amount"],datas["result_code"]=="0"?"�ɹ�":"ʧ��",datas["order_id"],datas["trade_id"],replace_string(datas["pay_time"],"%20"," ")));
	}
}

void set_persistent(int which)
{
	persistent = which;
}

